// https://zig.news/kristoff/how-to-add-buffering-to-a-writer-reader-in-zig-7jd
const std = @import("std");

pub fn main() !void {
    var readerWrapper = std.io.bufferedReader(std.io.getStdIn().reader());
    var r = readerWrapper.reader();
    var buffer: [std.mem.page_size]u8 = undefined;

    var nlines: u64 = 0;
    var nwords: u64 = 0;
    var last: u8 = ' ';
    var nbytes: u64 = 0;

    var bytes_read: u64 = 0;

    while (true) {
        bytes_read = try r.read(buffer[0..]);
        if (bytes_read == 0) {
            break;
        }
        for (buffer[0..bytes_read]) |c| {
            if (c == '\n') {
                nlines += 1;
            }

            if (!std.ascii.isWhitespace(c) and std.ascii.isWhitespace(last)) {
                nwords += 1;
            }
            last = c;
        }
        nbytes += bytes_read;
    }
    const stdout = std.io.getStdOut().writer();
    nosuspend stdout.print("{d}\t{d}\t{d}\n", .{ nlines, nwords, nbytes }) catch return;
}
