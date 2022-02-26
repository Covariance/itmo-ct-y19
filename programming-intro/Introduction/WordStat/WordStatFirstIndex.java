import java.io.*;
import java.util.LinkedHashMap;
import java.util.Map;

public class WordStatFirstIndex {
    private static final Skippable WORD_SKIPPER = new WordSkippablePattern();

    static class WordSkippablePattern implements Skippable {
        public boolean isSkippable(int codePoint) {
            return codePoint != '\'' && Character.getType(codePoint) != Character.DASH_PUNCTUATION && !Character.isLetter(codePoint);
        }
    }

    public static void main(String[] args) {
        if (args.length < 2) {
            System.err.println("Not enough arguments");
            return;
        }

        Map<String, IntListFirst> text = new LinkedHashMap<>();

        try {
            Scanner scan = new Scanner(new File(args[0]), "utf-8", WORD_SKIPPER);
            int lineIndex = 0;
            try {
                while (scan.hasNextLine()) {
                    int indexInLine = 1;
                    Scanner lineScan = new Scanner(scan.nextLine().toLowerCase(), WORD_SKIPPER);
                    while (lineScan.hasNextWord()) {
                        String word = lineScan.nextWord();
                        IntListFirst currentWord = text.get(word);
                        if (currentWord == null) {
                            currentWord = new IntListFirst();
                            text.put(word, currentWord);
                        }
                        currentWord.add(indexInLine++, lineIndex);
                    }
                    lineIndex++;
                }
            } finally {
                scan.close();
            }
        } catch (FileNotFoundException e) {
            System.out.println("Input file not found: " + e.getMessage());
            return;
        } catch (UnsupportedEncodingException e) {
            System.out.println("Unicode encoding for input file not supported: " + e.getMessage());
            return;
        } catch (IOException e) {
            System.out.println("I/O error occurred while reading: " + e.getMessage());
            return;
        }

        try {
            BufferedWriter output = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(args[1]), "utf-8"));

            try {
                for (Map.Entry<String, IntListFirst> current : text.entrySet()) {
                    output.write(current.getValue().printEntry(current.getKey()));
                    output.newLine();
                }
            } catch (IOException e) {
                System.out.println("I/O error occurred while trying to print: " + e.getMessage());
            } finally {
                output.close();
            }
        } catch (FileNotFoundException e) {
            System.out.println("Output file cannot be created: " + e.getMessage());
        } catch (IOException e) {
            System.out.println("IOException occurred during writing:: " + e.getMessage());
        }
    }
}
