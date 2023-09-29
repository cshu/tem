#[derive(Debug)]
struct DropEg;

impl Drop for DropEg {
    fn drop(&mut self) {
        println!("Dropping DropEg!");
    }
}
fn main() {
    let _x = DropEg {};
    {
        let temfn = move |needle| println!("{:?}, {:?}", needle, _x);
        //println!("{:?}", _x);//NOTE! this line does not work because ownership has been taken
        temfn(1);
        temfn(2);
        println!("scope END");
        //NOTE! dropping happens after scope ends
    }
    //println!("{:?}", _x);//NOTE! this line does not work because ownership has been taken
    println!("END");
}
