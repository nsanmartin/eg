// https://zig.news/kristoff/how-to-add-buffering-to-a-writer-reader-in-zig-7jd

const std = @import("std");

pub fn main() !void {
    var readerWrapper = std.io.bufferedReader(std.io.getStdIn().reader());
    var r = readerWrapper.reader();
    var buffer: [std.mem.page_size]u8 = undefined;

    var writerWrapper = std.io.bufferedWriter(std.io.getStdOut().writer());
    var w = writerWrapper.writer();

    var bytes_read = try r.read(buffer[0..]);
    while (bytes_read > 0) {
        nosuspend w.print("{s}", .{buffer[0..bytes_read]}) catch return;
        bytes_read = try r.read(buffer[0..]);
    }
    try writerWrapper.flush();
}
