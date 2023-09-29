use std::*;

//add various functions calling std functions to demonstrate featues in std library

fn main() {
    let args: Vec<String> = env::args().collect(); //Note that std::env::args will panic if any argument contains invalid Unicode.
    match args[1].as_str() {
        "canonicalize" => {
            println!("{:?}", std::fs::canonicalize(&args[2]));
        }
        "byte-occurrence" => {
            let filepb = std::fs::canonicalize(&args[2]).unwrap();
            let byt = args[3].as_bytes()[0];
            let bytes = fs::read(filepb).unwrap();
            let mut iterobj = bytes.iter();
            let mut count = 0;
            while iterobj.rposition(|ibyt| *ibyt == byt).is_some() {
                count += 1;
            }
            println!("{}", count);
        }
        _ => {}
    }
    println!("Hello, world!");
}
