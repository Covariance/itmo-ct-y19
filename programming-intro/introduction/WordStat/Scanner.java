import java.io.*;
import java.util.NoSuchElementException;

///Exceptions

interface Skippable {
    boolean isSkippable(int codePoint);
}

interface PatternMatcher {
    boolean matchesPattern(String str);
}

class DefaultSkippablePattern implements Skippable {
    public boolean isSkippable(int codePoint) {
        return Character.isWhitespace(codePoint) || (codePoint == '\n') || (codePoint == '\r');
    }
}

class IntegerPatternMatcher implements PatternMatcher {
    public boolean matchesPattern(String str) {
        try {
            int a = Integer.parseInt(str);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }
}

class WordPatternMatcher implements PatternMatcher {
    private boolean isWordCharacter(int codePoint) {
        return (codePoint == '\'' || Character.getType(codePoint) == Character.DASH_PUNCTUATION || Character.isLetter(codePoint));
    }

    public boolean matchesPattern(String str) {
        if (str.length() == 0) {
            return false;
        }
        for (int i = 0; i < str.length(); i++) {
            if (!isWordCharacter(str.codePointAt(i))) {
                return false;
            }
        }
        return true;
    }
}

public class Scanner {
    /// The reader itself
    private Reader in;

    /// State of scanner
    private boolean closed;

    /// Indicates whether scanner is closed
    private boolean scannerClosed;

    /// Buffer of characters
    private char[] buf;

    /// For navigation in cached string
    private int currentPosition;
    private int currentSize;

    /// Last token for hasNext methods
    private String cachedLine;

    /// Method to extract tokens
    private Skippable skipper;

    /// Patterns for ints and words
    public static final IntegerPatternMatcher INT_MATCHER = new IntegerPatternMatcher();
    public static final WordPatternMatcher WORD_MATCHER = new WordPatternMatcher();

    /// Support functions
    private boolean isLineSeparator(int codePoint) {
        return  (codePoint == '\n') || (codePoint == '\r');
    }

    //region Constructors
    // Main constructor
    public Scanner(Reader reader, int buf_len, Skippable skipper) {
        this.in = reader;
        this.buf = new char[buf_len];
        this.closed = false;
        this.currentPosition = 0;
        this.currentSize = 0;
        this.cachedLine = null;
        this.skipper = skipper;
    }

    /// Constructors from InputStreams
    public Scanner(InputStream is) {
        this(new InputStreamReader(is), 1024, new DefaultSkippablePattern());
    }

    public Scanner(InputStream is, int len) {
        this(new InputStreamReader(is), len, new DefaultSkippablePattern());
    }

    public Scanner(InputStream is, String charsetName) throws UnsupportedEncodingException {
        this(new InputStreamReader(is, charsetName), 1024, new DefaultSkippablePattern());
    }

    public Scanner(InputStream is, String charsetName, int len) throws UnsupportedEncodingException {
        this(new InputStreamReader(is, charsetName), len, new DefaultSkippablePattern());
    }

    public Scanner(InputStream is, Skippable skipper) {
        this(new InputStreamReader(is), 1024, skipper);
    }

    public Scanner(InputStream is, int len, Skippable skipper) {
        this(new InputStreamReader(is), len, skipper);
    }

    public Scanner(InputStream is, String charsetName, Skippable skipper) throws UnsupportedEncodingException {
        this(new InputStreamReader(is, charsetName), 1024, skipper);
    }

    public Scanner(InputStream is, String charsetName, int len, Skippable skipper) throws UnsupportedEncodingException {
        this(new InputStreamReader(is, charsetName), len, skipper);
    }

    /// Constructors from files
    public Scanner(File file) throws FileNotFoundException {
        this(new InputStreamReader(new FileInputStream(file)), 1024, new DefaultSkippablePattern());
    }

    public Scanner(File file, int len) throws FileNotFoundException {
        this(new InputStreamReader(new FileInputStream(file)), len, new DefaultSkippablePattern());
    }

    public Scanner(File file, String charsetName) throws FileNotFoundException, UnsupportedEncodingException {
        this(new InputStreamReader(new FileInputStream(file), charsetName), 1024, new DefaultSkippablePattern());
    }

    public Scanner(File file, String charsetName, int len) throws FileNotFoundException, UnsupportedEncodingException {
        this(new InputStreamReader(new FileInputStream(file), charsetName), len, new DefaultSkippablePattern());
    }

    public Scanner(File file, Skippable skipper) throws FileNotFoundException {
        this(new InputStreamReader(new FileInputStream(file)), 1024, skipper);
    }

    public Scanner(File file, int len, Skippable skipper) throws FileNotFoundException {
        this(new InputStreamReader(new FileInputStream(file)), len, skipper);
    }

    public Scanner(File file, String charsetName, Skippable skipper) throws FileNotFoundException, UnsupportedEncodingException {
        this(new InputStreamReader(new FileInputStream(file), charsetName), 1024, skipper);
    }

    public Scanner(File file, String charsetName, int len, Skippable skipper) throws FileNotFoundException, UnsupportedEncodingException {
        this(new InputStreamReader(new FileInputStream(file), charsetName), len, skipper);
    }

    /// Constructors from strings
    public Scanner(String string) {
        this(new StringReader(string), 1024, new DefaultSkippablePattern());
    }

    public Scanner(String string, int len) {
        this(new StringReader(string), len, new DefaultSkippablePattern());
    }

    public Scanner(String string, Skippable skipper) {
        this(new StringReader(string), 1024, skipper);
    }

    public Scanner(String string, int len, Skippable skipper) {
        this(new StringReader(string), len, skipper);
    }
    //endregion

    /// Class functions
    public void close() throws IOException {
        if (scannerClosed) {
            return;
        }
        in.close();
        in = null;
        buf = null;
        scannerClosed = true;
    }

    private boolean updateBuffer() throws IOException {
        currentSize = in.read(buf);
        currentPosition = 0;
        return (currentSize > 0);
    }

    public boolean hasNext() throws IOException, IllegalStateException {
        if (scannerClosed) {
            throw new IllegalStateException("Scanner is closed");
        }
        if ((currentSize <= 0 || currentPosition >= currentSize) && (cachedLine == null)) {
            return updateBuffer();
        }
        return true;
    }

    private boolean moveToNextToken() throws IOException {
        while (hasNext() && skipper.isSkippable(buf[currentPosition])) {
            currentPosition++;
        }
        return hasNext();
    }

    public boolean hasNextToken() throws IOException, IllegalStateException {
        if (scannerClosed) {
            throw new IllegalStateException("Scanner is closed");
        }
        return ((cachedLine != null) || moveToNextToken());
    }

    private void cacheNextToken() throws IOException, NoSuchElementException {
        if (!moveToNextToken()) {
            throw new NoSuchElementException("There's no token to cache");
        }
        int startingPoint = currentPosition;
        StringBuilder retv = new StringBuilder();
        while (hasNext()) {
            while (currentPosition < currentSize && !skipper.isSkippable((int)(buf[currentPosition]))) {
                currentPosition++;
            }
            retv.append(buf, startingPoint, currentPosition - startingPoint);
            if (currentPosition == currentSize) {
                startingPoint = 0;
            } else {
                break;
            }
        }
        cachedLine = retv.toString();
    }

    public boolean hasNextPattern(PatternMatcher patternMatcher) throws IOException, IllegalStateException{
        if (scannerClosed) {
            throw new IllegalStateException("Scanner is closed");
        }

        if (!hasNextToken()) {
            return false;
        }

        if (cachedLine == null) {
            cacheNextToken();
        }

        return patternMatcher.matchesPattern(cachedLine);
    }

    public String nextPattern(PatternMatcher patternMatcher) throws IOException, NoSuchElementException, IllegalStateException {
        if (scannerClosed) {
            throw new IllegalStateException("Scanner is closed");
        }

        if (!hasNextPattern(patternMatcher)) {
            throw new NoSuchElementException("No pattern in the input");
        }

        String retv = cachedLine;
        cachedLine = null;
        return retv;
    }

    public boolean hasNextInt() throws IOException, IllegalStateException {
        return hasNextPattern(INT_MATCHER);
    }

    public int nextInt() throws IOException, NoSuchElementException, IllegalStateException {
        return Integer.parseInt(nextPattern(INT_MATCHER));
    }

    public boolean hasNextWord() throws IOException, IllegalStateException {
        return hasNextPattern(WORD_MATCHER);
    }

    public String nextWord() throws IOException, NoSuchElementException, IllegalStateException {
        return nextPattern(WORD_MATCHER);
    }

    public boolean hasNextLine() throws IOException, IllegalStateException{
        return hasNext();
    }

    public String nextLine() throws IOException, NoSuchElementException, IllegalStateException {
        if (scannerClosed) {
            throw new IllegalStateException("Scanner is closed");
        }

        if(!hasNextLine()) {
            throw new NoSuchElementException("No next line in the input");
        }

        StringBuilder retv = new StringBuilder();
        if (cachedLine != null) {
            retv.append(cachedLine);
            cachedLine = null;
        }

        int startingPoint = currentPosition;

        while (hasNext()) {
            while (currentPosition < currentSize && !isLineSeparator(buf[currentPosition])) {
                currentPosition++;
            }
            retv.append(buf, startingPoint, currentPosition - startingPoint);
            if (currentPosition == currentSize) {
                startingPoint = 0;
            } else {
                currentPosition++;
                break;
            }
        }
        hasNext();
        boolean doubleSeparator = (System.getProperty("line.separator").length() == 2 && buf[currentPosition] == '\r');
        currentPosition++;
        hasNext();
        if (doubleSeparator) {
            currentPosition++;
            hasNext();
        }
        return retv.toString();
    }

}