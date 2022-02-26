import java.io.*;
import java.util.NoSuchElementException;

public class OneCharScanner {
    public static final IntegerPatternMatcher INT_MATCHER = new IntegerPatternMatcher();
    /// The reader itself
    private Reader in;

    /// State of scanner
    private boolean closed;

    /// Indicates whether scanner is closed
    private boolean scannerClosed;

    /// Buffer of character (now not characterS)
    private char buf;

    /// For navigation with buffer
    private boolean isRead;

    /// Last token for hasNext methods
    private String cachedLine;

    /// Method to extract tokens
    private Skippable skipper;

    /// Support functions

    private boolean isLineSeparator(int codePoint) {
        return  (codePoint == '\n') || (codePoint == '\r');
    }

    //region Constructors
    // Main constructor
    public OneCharScanner(Reader reader, Skippable skipper) {
        this.in = reader;
        this.isRead = true;
        this.closed = false;
        this.cachedLine = null;
        this.skipper = skipper;
    }

    /// Constructors from InputStreams
    public OneCharScanner(InputStream is) {
        this(new InputStreamReader(is), new DefaultSkippablePattern());
    }


    public OneCharScanner(InputStream is, String charsetName) throws UnsupportedEncodingException {
        this(new InputStreamReader(is, charsetName), new DefaultSkippablePattern());
    }

    public OneCharScanner(InputStream is, Skippable skipper) {
        this(new InputStreamReader(is), skipper);
    }

    public OneCharScanner(InputStream is, String charsetName, Skippable skipper) throws UnsupportedEncodingException {
        this(new InputStreamReader(is, charsetName), skipper);
    }

    /// Constructors from files
    public OneCharScanner(File file) throws FileNotFoundException {
        this(new InputStreamReader(new FileInputStream(file)), new DefaultSkippablePattern());
    }

    public OneCharScanner(File file, String charsetName) throws FileNotFoundException, UnsupportedEncodingException {
        this(new InputStreamReader(new FileInputStream(file), charsetName), new DefaultSkippablePattern());
    }


    public OneCharScanner(File file, Skippable skipper) throws FileNotFoundException {
        this(new InputStreamReader(new FileInputStream(file)), skipper);
    }


    public OneCharScanner(File file, String charsetName, Skippable skipper) throws FileNotFoundException, UnsupportedEncodingException {
        this(new InputStreamReader(new FileInputStream(file), charsetName), skipper);
    }


    /// Constructors from strings
    public OneCharScanner(String string) {
        this(new InputStreamReader(new ByteArrayInputStream(string.getBytes())), new DefaultSkippablePattern());
    }


    public OneCharScanner(String string, String charsetName) throws UnsupportedEncodingException {
        this(new InputStreamReader(new ByteArrayInputStream(string.getBytes(charsetName)), charsetName), new DefaultSkippablePattern());
    }


    public OneCharScanner(String string, Skippable skipper) {
        this(new InputStreamReader(new ByteArrayInputStream(string.getBytes())), skipper);
    }


    public OneCharScanner(String string, String charsetName, Skippable skipper) throws UnsupportedEncodingException {
        this(new InputStreamReader(new ByteArrayInputStream(string.getBytes(charsetName)), charsetName), skipper);
    }

    //endregion

    /// Class functions
    public void close() throws IOException {
        if (scannerClosed) {
            return;
        }
        in.close();
        in = null;
        scannerClosed = true;
    }

    private boolean updateBuffer() throws IOException {
        int r = in.read();
        if (r == -1) {
            isRead = true;
            return false;
        }
        isRead = false;
        buf = (char) r;
        return true;
    }

    public boolean hasNext() throws IOException, IllegalStateException {
        if (scannerClosed) {
            throw new IllegalStateException("Scanner is closed");
        }
        return (!isRead || updateBuffer());
    }

    private boolean moveToNextToken() throws IOException {
        while (hasNext() && skipper.isSkippable(buf)) {
            isRead = true;
        }
        return hasNext();
    }

    public boolean hasNextToken() throws IOException, IllegalStateException {
        if (scannerClosed) {
            throw new IllegalStateException("Scanner is closed");
        }
        return ((cachedLine != null) || moveToNextToken());
    }

    public void cacheNextToken() throws IOException, NoSuchElementException {
        if (!moveToNextToken()) {
            throw new NoSuchElementException("There's no token to cache");
        }

        StringBuilder retv = new StringBuilder();
        while (hasNext() && !skipper.isSkippable((int) (buf))) {
                retv.append(buf);
                isRead = true;
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
        return hasNextPattern(new WordPatternMatcher());
    }

    public String nextWord() throws IOException, NoSuchElementException, IllegalStateException {
        return nextPattern(new WordPatternMatcher());
    }

    public boolean hasNextLine() throws IOException, IllegalStateException{
        return hasNext();
    }

    public String nextLine() throws IOException, NoSuchElementException, IllegalStateException {
        if (scannerClosed) {
            throw new IllegalStateException("Scanner is closed");
        }

        if (!hasNextLine()) {
            throw new NoSuchElementException("No next line in the input");
        }

        StringBuilder retv = new StringBuilder();
        if (cachedLine != null) {
            retv.append(cachedLine);
            cachedLine = null;
        }

        while (hasNext() && !isLineSeparator(buf)) {
            isRead = true;
            retv.append(buf);
        }

        if (hasNext()) {
            if (buf == '\r') {
                updateBuffer();
            }
            updateBuffer();
        }

        return retv.toString();
    }

}