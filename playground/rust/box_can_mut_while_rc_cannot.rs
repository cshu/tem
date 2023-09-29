use std::cell::*;
use std::rc::*;

fn print_type_of<T>(_: &T) {
    println!("{}", std::any::type_name::<T>())
}

fn main() {
    {
        let v1 = vec![1, 2, 3, 4];
        let mut b1 = Box::new(v1);
        (*b1).push(5);
        println!("{:?}", b1);
    }
    {
        let v2 = vec![1, 2, 3, 4];
        let mut r1 = Rc::new(v2);
        println!("{:?}", r1);
        //(*r1).push(5);//this line does not work!
    }
    println!("END");
}
