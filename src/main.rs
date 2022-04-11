mod presents;
mod weather;

fn main() {
    let args: Vec<String> = std::env::args().collect();
    if args.len() < 1 {println!(" Error: input program to run."); return}
    let program_to_run = String::from(&args[1]);

    if program_to_run == "presents" {presents::run()}
    else if program_to_run == "weather" {weather::run()}
    else {println!("Please enter valid program name. {:?} is not valid.", program_to_run);}
}
