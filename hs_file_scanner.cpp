

static int on_match(unsigned int id, unsigned long long from, unsigned long long to, unsigned int flags, void *ctx) {
    const char* path = static_cast<const char*>(ctx);
    printf("%s:%llu:%llu:id=%u\n", path, from, to, id);
    fprintf(stderr, "[on_match] %s %llu..%llu id=%u\n", path, from, to, id);
    return 0; 
}