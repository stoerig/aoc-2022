use std::fs::File;
use std::path::Path;
use std::{
    env,
    io::{self, BufRead},
};

type LineProcessor = fn(String) -> bool;

struct Section {
    start: u32,
    end: u32,
}

impl Section {
    fn init(start: u32, end: u32) -> Section {
        Section { start, end }
    }

    fn full_overlap(self, other: Section) -> bool {
        return (self.start >= other.start && self.end <= other.end)
            || (other.start >= self.start && other.end <= self.end);
    }

    fn any_overlap(self, other: Section) -> bool {
        return (self.start >= other.start && self.start <= other.end)
            || (other.start >= self.start && other.start <= self.end);
    }
}

fn part_one(line: String) -> bool {
    let (s1, s2): (Section, Section) = parse_line(line);
    return s1.full_overlap(s2);
}

fn parse_line(line: String) -> (Section, Section) {
    let res: Vec<u32> = line
        .split([',', '-'])
        .map(|number| number.parse::<u32>().unwrap())
        .collect();
    return (Section::init(res[0], res[1]), Section::init(res[2], res[3]));
}

fn part_two(line: String) -> bool {
    let (s1, s2): (Section, Section) = parse_line(line);
    return s1.any_overlap(s2);
}

fn main() {
    let mut result: u32 = 0;
    // File hosts must exist in current path before this produces output
    let part = env::var("part").unwrap_or("part1".to_string());

    let hit: LineProcessor = match &*part {
        "part2" => part_two,
        _ => part_one,
    };

    if let Ok(lines) = read_lines("input.txt") {
        // Consumes the iterator, returns an (Optional) String
        for line in lines {
            if let Ok(ip) = line {
                if hit(ip) {
                    result += 1;
                }
            }
        }
    }
    println!("Rust");
    println!("{}", result);
}

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where
    P: AsRef<Path>,
{
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}
