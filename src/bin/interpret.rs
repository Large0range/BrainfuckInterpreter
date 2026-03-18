use std::collections::VecDeque;
use std::env;
use std::fs;

fn main() {
    let filename = env::args().nth(1).expect("No filename provided");
    let contents = fs::read_to_string(filename).expect("Could not find file").to_ascii_lowercase();

    let tokens: Vec<char> = contents.chars().filter(|c| matches!(c, ',' | '.' | '+' | '-' | '<' | '>' | '[' | ']')).collect(); // strips the program to only valid tokens
    let size = tokens.len();

    let mut stack: VecDeque<usize> = Default::default();

    let mut tape: [u8; 30000] = [0; 30000];
    let mut tape_index: usize = 0;
    
    let mut program_location = 0;
    while program_location < size {
        match tokens[program_location] {
            '>' => {tape_index = (tape_index + 1) % tape.len();}
            '<' => {tape_index = (tape_index  + tape.len() - 1) % tape.len();}
            '+' => {tape[tape_index] = tape[tape_index].wrapping_add(1);}
            '-' => {tape[tape_index] = tape[tape_index].wrapping_sub(1)}
            '.' => {print!{"{}", tape[tape_index] as char};}
            '[' => {
                if tape[tape_index] == 0 {
                    let mut nest = 1;
                    while nest > 0 {
                        program_location += 1;
                        if program_location >= size {
                            panic!("Unpaired [");
                        }

                        match tokens[program_location]  {
                            ']' => {nest -= 1}
                            '[' => {nest += 1}
                            _ => {}
                        }
                    }

                } else {
                    stack.push_back(program_location); 
                }
            }


            ']' => {
                if tape[tape_index] != 0 {
                    program_location = *stack.back().expect("Unpaired ]");
                } else {
                    stack.pop_back().expect("");
                }
            }
            _ => {}
        }

        program_location += 1;
    } 

    /*
    for x in tokens {
        match x {
            '>' => {index = (index + 1) % tape.len();}
            '<' => {index = (index  + tape.len() - 1) % tape.len();}
            '+' => {tape[index] = tape[index].wrapping_add(1);}
            '-' => {tape[index] = tape[index].wrapping_sub(1)}
            '.' => {print_tape(&tape);}
            '[' => {}
            _ => {println!("{x} is not period");}
        }
    } */
}
