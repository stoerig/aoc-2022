const std = @import("std");
const fs = @import("fs");

const Move = enum(u3) {
    rock = 1,
    paper = 2,
    scissors = 3
};

const RoundWinner = enum(u4) {
    player = 6,
    opponent = 0,
    draw = 3,
};

const DeterminedWinner = enum(u2) {
    opponent,
    draw,
    player
};

fn determinePlayerMove(opponentMove: Move, determinedWinner: DeterminedWinner) Move {
    return switch (determinedWinner) {
        .opponent => return switch (opponentMove) {
            .rock => .scissors,
            .paper => .rock,
            .scissors => .paper,
        },
        .draw => opponentMove,
        .player => return switch (opponentMove) {
            .rock => .paper,
            .paper => .scissors,
            .scissors => .rock,
        },
    };
}

fn playRound(opponentMove: Move, playerMove: Move) RoundWinner {
    return switch (playerMove) {
        .rock => return switch (opponentMove) {
            .rock => RoundWinner.draw,
            .scissors => RoundWinner.player,
            .paper => RoundWinner.opponent,
        },
        .paper => return switch (opponentMove) {
            .paper => RoundWinner.draw,
            .rock => RoundWinner.player,
            .scissors => RoundWinner.opponent,
        },
        .scissors => return switch (opponentMove) {
            .scissors => RoundWinner.draw,
            .paper => RoundWinner.player,
            .rock => RoundWinner.opponent,
        },
    };
}

fn scoreRound(opponentMove : Move, playerMove: Move) u32 {
    const res = playRound(opponentMove, playerMove);

    return @enumToInt(res) + @enumToInt(playerMove);
}

fn toMove(input: u8) Move {
    return switch (input) {
        'A' => Move.rock,
        'X' => Move.rock,
        'B' => Move.paper,
        'Y' => Move.paper,
        'C' => Move.scissors,
        'Z' => Move.scissors,
        else => Move.rock,
    };
}

fn toDeterminedWinner(input: u8) DeterminedWinner {
    return switch (input) {
        'X' => DeterminedWinner.opponent,
        'Y' => DeterminedWinner.draw,
        'Z' => DeterminedWinner.player,
        else => DeterminedWinner.draw,
    };
}

fn partTwo(opponentCollumn: u8, playerCollumn :u8) u32 {

    const winner : DeterminedWinner = toDeterminedWinner(playerCollumn);
    const opponentMove = toMove(opponentCollumn);
    const playerMove = determinePlayerMove(opponentMove, winner);
    const roundScore = scoreRound(opponentMove, playerMove);
    return roundScore;
}
fn partOne(opponentCollumn: u8, playerCollumn :u8) u32 {
    const opponentMove = toMove(opponentCollumn);
    const playerMove = toMove(playerCollumn);

    const roundScore = scoreRound(opponentMove, playerMove);

    return roundScore;
}

pub fn main() !void {
    const stdout = std.io.getStdOut().writer();

    var file = try std.fs.cwd().openFile("input.txt", .{});
    defer file.close();

    var buf_reader = std.io.bufferedReader(file.reader());
    var in_stream = buf_reader.reader();

    var buffer: [10000]u8 = undefined;

    const part = std.os.getenv("part") orelse "part1";

    const isPartOne = std.mem.eql(u8, part, "part1");

    var totalScore: u32 = 0;

    while (try in_stream.readUntilDelimiterOrEof(&buffer, '\n')) |line| {
        totalScore += if (isPartOne) partOne(line[0], line[2]) else partTwo(line[0], line[2]);
    }

    try stdout.print("{s}\n{any}\n", .{"Zig",totalScore});
}

