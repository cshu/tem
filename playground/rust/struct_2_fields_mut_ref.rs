use std::any::type_name;

fn print_type_of<T>(_: &T) {
    println!("{}", std::any::type_name::<T>())
}

fn type_of<T>(_: T) -> &'static str {
    type_name::<T>()
}

//a good post here: https://oribenshir.github.io/afternoon_rusting/blog/mutable-reference
//it says "the Rust compiler is being smart. It understands some basics concepts about structs, and it knows that borrows can be “split.” Meaning that while we are not allowed to take two mutable references to the entire struct, we can have up to one mutable reference for each of the struct fields. In this case, it is okay to have two mutable references, one to the field a and another to b, as at no point in time, we have two mutable references to the same piece of data in memory. But the Rust compiler has its limitations. Once we extracted a function, it is not smart enough to understand the method uses only one field in self. It automatically mutably borrow the entire struct."

struct Mf {
    x: Vec<i32>,
    y: Vec<i32>,
}

impl Mf {
    fn mutate_f(&mut self) {
        let mut xr_2 = &mut self.x;
        println!("{}", type_of(xr_2));
        let mut xr = &mut self.x;
        let mut yr = &mut self.y;
        print_type_of(&xr);
        let elem_rx = &mut xr[1];
        let elem_ry = &mut yr[1];
        //let elem_ry_2 = &mut yr[0];//this does not work. You need util fn like split_at_mut
        *elem_rx = 41; //this is possilbe only before xr.push()!! NOT after!!
        xr.push(11);
        *elem_ry = 42; //this is possilbe only before yr.push()!! NOT after!!
        yr.push(12);
    }
}

fn main() {
    {
        let mut mf = Mf {
            x: vec![1, 2],
            y: vec![2, 1],
        };
        mf.mutate_f();
        println!("{:?}", mf.x);
        println!("{:?}", mf.y);
    }
    println!("END");
}
