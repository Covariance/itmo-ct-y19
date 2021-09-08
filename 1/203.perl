while (<>) {
    s/(\b)([Aa]+)(\b)/\1argh\3/;
    print;
}