import java.io.*;
import java.util.LinkedHashMap;
import java.util.Map;

public class WordStatIndex
{

    public static boolean isLegitCharacter(int codePoint) {
        return ((codePoint == '\'') || (Character.getType(codePoint) == Character.DASH_PUNCTUATION) || Character.isLetter(codePoint));
    }

    static class WordSkippablePattern implements Skippable {
        public boolean isSkippable(int codePoint) {
            return !isLegitCharacter(codePoint);
        }
    }

    public static void main(String[] args) {
        final WordSkippablePattern WORD_SKIPPER = new WordSkippablePattern();

        if (args.length < 2) {
            System.err.println("Not enough arguments");
            return ;
        }

        Map<String, IntList> text = new LinkedHashMap<String, IntList>();

        try {
            Scanner scan = new Scanner(new File(args[0]), "utf-8", WORD_SKIPPER);
            String line;
            try {
                int indexInLine = 1;
                while (scan.hasNextLine()) {
                    line = scan.nextLine().toLowerCase();
                    Scanner lineScan = new Scanner(line, WORD_SKIPPER);
                    while (lineScan.hasNextWord()) {
                        String word = lineScan.nextWord();
                        IntList currentWord = text.get(word);
                        if (currentWord == null) {
                            text.put(word, new IntList(indexInLine));
                        } else {
                            currentWord.add(indexInLine);
                        }
                        indexInLine++;
                    }
                }
            } catch (IOException e) {
                System.out.println("I/O error occurred while reading: " + e.getMessage());
            } finally {
                scan.close();
            }
        } catch (FileNotFoundException e) {
            System.out.println("Input file not found: " + e.getMessage());
        } catch (UnsupportedEncodingException e) {
            System.out.println("Unicode encoding for input file not supported: " + e.getMessage());
        } catch (IOException e) {
            System.out.println("I/O error while trying to close input scanner: " + e.getMessage());
        }

        try {
            BufferedWriter output = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(args[1]), "utf-8"));

            try {
                for (Map.Entry<String, IntList> current : text.entrySet()) {
                    StringBuilder result = new StringBuilder();
                    result.append(current.getKey()).append(' ');
                    result.append(current.getValue().size()).append(' ');
                    for (int i = 0; i < current.getValue().size(); i++) {
                        result.append(current.getValue().get(i));
                        if (i + 1 != current.getValue().size()) {
                            result.append(' ');
                        }
                    }
                    result.append('\n');
                    output.write(result.toString());
                }
            } catch (IOException e) {
                System.out.println("I/O error occurred while trying to print: " + e.getMessage());
            } finally {
                output.close();
            }

        } catch (FileNotFoundException e) {
            System.out.println("Output file not found: " + e.getMessage());
        } catch (IOException e) {
            System.out.println("Unicode encoding for output file not supported: " + e.getMessage());
        }
    }
}