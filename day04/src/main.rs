use std::fs::File;
use std::path::Path;
use std::{
    env,
    io::{self, BufRead},
};

type LineProcessor = fn(String) -> u32;

struct Section {
    data: [[u32; 2]; 2],
}

impl Section {
    fn full_overlap(self) -> bool {
        return (self.data[0][0] <= self.data[1][0] && self.data[0][1] >= self.data[1][1])
            || (self.data[1][0] <= self.data[0][0] && self.data[1][1] >= self.data[0][1]);
    }

    fn any_overlap(self) -> bool {
        return (self.data[0][0] <= self.data[1][0]) || (self.data[1][0] <= self.data[0][0]);
    }
}

fn part_one(line: String) -> u32 {
    let s: Section = parse_line(line);
    if s.full_overlap() {
        return 1;
    } else {
        return 0;
    }
}

fn parse_line(line: String) -> Section {
    let mut s: Section = Section {
        data: [[0; 2], [0; 2]],
    };

    for (k, section) in line.split(',').enumerate() {
        for (i, number) in section.split('-').enumerate() {
            let n = number.parse::<u32>().unwrap();
            s.data[k][i] = n;
        }
    }

    return s;
}

fn part_two(line: String) -> u32 {
    let s: Section = parse_line(line);

    if s.any_overlap() {
        return 1;
    } else {
        return 0;
    }
}

fn main() {
    let mut result: u32 = 0;
    // File hosts must exist in current path before this produces output
    let part = env::var("part").unwrap_or("part1".to_string());

    let process_line: LineProcessor = match &*part {
        "part2" => part_two,
        _ => part_one,
    };

    if let Ok(lines) = read_lines("input.txt") {
        // Consumes the iterator, returns an (Optional) String
        for line in lines {
            if let Ok(ip) = line {
                result += process_line(ip);
            }
        }
    }
    println!("{}", result);
}

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where
    P: AsRef<Path>,
{
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}
