while (<>) {
    s/\(.*?\)/\(\)/g;
    print;
}