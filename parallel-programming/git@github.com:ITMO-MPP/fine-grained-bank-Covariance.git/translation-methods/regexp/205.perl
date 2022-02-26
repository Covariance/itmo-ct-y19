while (<>) {
    s/\b(\w)(\B\w)(\w*?)\b/\2\1\3/g;
    print;
}