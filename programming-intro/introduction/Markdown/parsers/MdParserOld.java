package markup.parsers;

import javafx.util.Pair;
import markup.*;

import java.util.Arrays;

import static java.lang.Math.min;

public class MdParserOld {
    static final protected String[] STRONG_DELIMITER = {"**", "__"};
    static final protected String[] EMPHASIS_DELIMITER = {"*", "_"};
    static final protected String[] STRIKEOUT_DELIMITER = {"--", "~~"};
    static final protected String[] CODE_DELIMITER = {"`"};
    static final protected int STRONG_TAG_LENGTH = 2;
    static final protected int EMPHASIS_TAG_LENGTH = 1;
    static final protected int STRIKEOUT_TAG_LENGTH = 2;
    static final protected int CODE_TAG_LENGTH = 1;


    protected static Pair<Integer, Integer> findDelimiter(String string, int left, int right, String[] delimiters, int delimiterLength) {
        Pair<Integer, Integer>[] candidates = new Pair[delimiters.length];
        for (int j = 0; j < delimiters.length; j++) {
            boolean leftBorderFound = false;
            int leftBorder = right, rightBorder = right;
            for (int i = left; i < right; i++) {
                if (string.charAt(i) == '\\') {
                    i++;
                    continue;
                }
                if (string.regionMatches(i, delimiters[j], 0, delimiterLength)) {
                    if (leftBorderFound) {
                        rightBorder = i;
                        break;
                    } else {
                        leftBorder = i;
                        leftBorderFound = true;
                        i += delimiterLength - 1;
                    }
                }
            }
            candidates[j] = new Pair<>(leftBorder, rightBorder);
        }
        Pair<Integer, Integer> best = new Pair<>(string.length(), string.length());
        for (int j = 0; j < candidates.length; j++) {
            if (best.getKey() > candidates[j].getKey() && candidates[j].getValue() != string.length()) {
                best = candidates[j];
            }
        }
        return best;
    }

    private static int isHeader(String text) {
        int len = 0;
        while (len < text.length() && text.charAt(len) == '#') {
            len++;
        }
        return (len == text.length() || len == 0 || text.charAt(len) != ' ') ? -1 : len;
    }

    private static String[] divideByBlocks(String text) {
        String[] result = new String[1];
        int size = 0;
        int l = 0, m;
        while ((m = text.indexOf("\n\n", l)) != -1) {
            if (size == result.length) {
                result = Arrays.copyOf(result, 2 * size);
            }
            result[size++] = text.substring(l, m);
            l = m + 2;
        }
        if (l != text.length()) {
            if (size == result.length) {
                result = Arrays.copyOf(result, 2 * size);
            }
            result[size++] = text.substring(l);
        }

        return Arrays.copyOf(result, size);
    }

    private static Paragraphable[] parseText(String text, int left, int right) {
        Paragraphable[] result = new Paragraphable[1];
        int currentLength = 0;
        for (int i = left; i < right; i++) {
            Pair<Integer, Integer> strong = findDelimiter(text, i, right, STRONG_DELIMITER, STRONG_TAG_LENGTH);
            Pair<Integer, Integer> emphasis = findDelimiter(text, i, right, EMPHASIS_DELIMITER, EMPHASIS_TAG_LENGTH);
            Pair<Integer, Integer> code = findDelimiter(text, i, right, CODE_DELIMITER, CODE_TAG_LENGTH);
            Pair<Integer, Integer> strikeout = findDelimiter(text, i, right, STRIKEOUT_DELIMITER, STRIKEOUT_TAG_LENGTH);
            int leftBorder = min(min(strong.getKey(), emphasis.getKey()), min(code.getKey(), strikeout.getKey()));
            if (strong.getValue().equals(code.getValue()) && code.getValue().equals(emphasis.getValue()) && emphasis.getValue().equals(strikeout.getValue())) {
                result = (result.length == currentLength) ? Arrays.copyOf(result, 2 * result.length) : result;
                result[currentLength++] = new Text(text.substring(i, right));
                i = text.length();
                continue;
            } else if (strong.getKey() == leftBorder) {
                result = (result.length == currentLength) ? Arrays.copyOf(result, 2 * result.length) : result;
                result[currentLength++] = new Text(text.substring(i, strong.getKey()));
                result = (result.length == currentLength) ? Arrays.copyOf(result, 2 * result.length) : result;
                result[currentLength++] = new Strong(
                        Arrays.asList(
                                parseText(
                                        text, strong.getKey() + STRONG_TAG_LENGTH, strong.getValue()
                                )
                        )
                );
                i = strong.getValue() + STRONG_TAG_LENGTH - 1;
                continue;
            } else if (emphasis.getKey() == leftBorder) {
                result = (result.length == currentLength) ? Arrays.copyOf(result, 2 * result.length) : result;
                result[currentLength++] = new Text(text.substring(i, emphasis.getKey()));
                result = (result.length == currentLength) ? Arrays.copyOf(result, 2 * result.length) : result;
                result[currentLength++] = new Emphasis(
                        Arrays.asList(
                                parseText(
                                        text, emphasis.getKey() + EMPHASIS_TAG_LENGTH, emphasis.getValue()
                                )
                        )
                );
                i = emphasis.getValue() + EMPHASIS_TAG_LENGTH - 1;
                continue;
            } else if (code.getKey() == leftBorder) {
                result = (result.length == currentLength) ? Arrays.copyOf(result, 2 * result.length) : result;
                result[currentLength++] = new Text(text.substring(i, code.getKey()));
                result = (result.length == currentLength) ? Arrays.copyOf(result, 2 * result.length) : result;
                result[currentLength++] = new Code(
                        Arrays.asList(
                                parseText(
                                        text, code.getKey() + CODE_TAG_LENGTH, code.getValue()
                                )
                        )
                );
                //result[currentLength++] = new UntaggedCode(workString.substring(code.getKey() + CODE_TAG_LENGTH, code.getValue()));
                i = code.getValue() + CODE_TAG_LENGTH - 1;
                continue;
            } else if (strikeout.getKey() == leftBorder) {
                result = (result.length == currentLength) ? Arrays.copyOf(result, 2 * result.length) : result;
                result[currentLength++] = new Text(text.substring(i, strikeout.getKey()));
                result = (result.length == currentLength) ? Arrays.copyOf(result, 2 * result.length) : result;
                result[currentLength++] = new Strikeout(
                        Arrays.asList(
                                parseText(
                                        text,strikeout.getKey() + STRIKEOUT_TAG_LENGTH, strikeout.getValue()
                                )
                        )
                );
                i = strikeout.getValue()  + STRIKEOUT_TAG_LENGTH - 1;
                continue;
            } else {
                System.err.println("UNEXPECTED STRING: " + text);
                continue;
            }
        }
        result = Arrays.copyOf(result, currentLength);
        return result;
    }

    private static Markable parseBlock(String block) {
        while (block.length() > 0 && block.charAt(0) == '\n') {
            block = block.substring(1);
        }
        int len = isHeader(block);
        if (len != -1) {
            String blockWithoutHeader = block.substring(len + 1);
            return (blockWithoutHeader.length() == 0) ? null : new Header(Arrays.asList(parseText(blockWithoutHeader, 0, blockWithoutHeader.length())), len);
        }
        return (block.length() == 0) ? null : new Paragraph(Arrays.asList(parseText(block, 0, block.length())));
    }

    @Deprecated
    public static void run() {
        String[] s = divideByBlocks("# Заголовок первого уровня\n" +
                "\n" +
                "## Второго\n" +
                "\n" +
                "### Третьего ## уровня\n" +
                "\n" +
                "#### Четвертого\n" +
                "# Все еще четвертого\n" +
                "\n" +
                "Этот абзац текста,\n" +
                "содержит две строки.\n" +
                "\n" +
                "    # Может показаться, что это заголовок.\n" +
                "Но нет, это абзац начинающийся с `#`.\n" +
                "\n" +
                "#И это не заголовок.\n" +
                "\n" +
                "###### Заголовки могут быть многострочными\n" +
                "(и с пропуском заголовков предыдущих уровней)\n" +
                "\n" +
                "Мы все любим *выделять* текст _разными_ способами.\n" +
                "**Сильное выделение**, используется гораздо реже,\n" +
                "но __почему бы и нет__?\n" +
                "Немного --зачеркивания-- еще ни кому не вредило.\n" +
                "Код представляется элементом `code`.\n" +
                "\n" +
                "Обратите внимание, как экранируются специальные\n" +
                "HTML-символы, такие как `<`, `>` и `&`.\n" +
                "\n" +
                "Знаете ли вы, что в Markdown, одиночные * и _\n" +
                "не означают выделение?\n" +
                "Они так же могут быть заэкранированы\n" +
                "при помощи обратного слэша: \\*.\n" +
                "\n" +
                "\n" +
                "\n" +
                "Лишние пустые строки должны игнорироваться.\n" +
                "\n" +
                "Любите ли вы *вложеные __выделения__* так,\n" +
                "как __--люблю--__ их я?");
        StringBuilder res;
        for (String str: s) {
            res = new StringBuilder();
            parseBlock(str).toHtml(res);
            System.out.println(res.toString());
        }
    }

    public static Content parseMd(String string) {
        String[] blocks = divideByBlocks(string);
        Markable parsedBlocks[] = new Markable[1], parsedBlock;
        int currentSize = 0;
        for (String block: blocks) {
             if ((parsedBlock = MdParserOld.parseBlock(block)) != null) {
                 parsedBlocks = (currentSize == parsedBlocks.length) ?  Arrays.copyOf(parsedBlocks, 2 * parsedBlocks.length) : parsedBlocks;
                 parsedBlocks[currentSize++] = parsedBlock;
                 parsedBlocks = (currentSize == parsedBlocks.length) ?  Arrays.copyOf(parsedBlocks, 2 * parsedBlocks.length) : parsedBlocks;
                 parsedBlocks[currentSize++] = new Text("\n");
             }
        }
        return new Content(Arrays.asList(Arrays.copyOf(parsedBlocks, currentSize - 1)));
    }
}
