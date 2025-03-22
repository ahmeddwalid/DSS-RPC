struct string_pair {
    string s1<>; /* First string, maximum length is arbitrary */
    string s2<>; /* Second string, maximum length is arbitrary */
};

program SUBSTRING_PROG {
    version SUBSTRING_VERS {
        bool IS_SUBSTRING(string_pair) = 1;
    } = 1;
} = 0xD2B44F1; /* A unique program number within range */
