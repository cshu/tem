use std::cell::*;
use std::rc::*;

fn print_type_of<T>(_: &T) {
    println!("{}", std::any::type_name::<T>())
}

//for multiple mut references to elements in vec/slice, see https://users.rust-lang.org/t/how-to-create-two-reference-to-different-elements-of-a-vec-when-at-least-one-is-mutable/56627
fn main() {
    {
        let v1 = vec![Some(Box::new(1)), Some(Box::new(2)), Some(Box::new(3))];
        let r1 = Rc::new(RefCell::new(v1));
        let r2 = Rc::clone(&r1);
        let mut bm = r2.borrow_mut();
        print_type_of(&bm);
        print_type_of(&*bm);
        println!("{:?}", r1); //fails to print because Debug trait impl calls try_borrow
        println!("{:?}", r2);
        println!("{:?}", bm);
        bm[1] = None;
        let ref_to_0 = &mut bm[0];
        print_type_of(&ref_to_0);
        print_type_of(ref_to_0);
        let mut dynamic_r: &mut Box<i32> = &mut (Box::new(998));
        let mut dynamic_o: Option<&mut Box<i32>> = None;
        println!("{:?}", dynamic_r);
        println!("{:?}", dynamic_o);
        match ref_to_0.as_mut() {
            Some(inn) => {
                print_type_of(&inn);
                print_type_of(inn);
                **inn = 999;
                dynamic_r = inn; //reassign!!

                //dynamic_o = Some(inn);//this line does not work cuz mut borrow happens once
            }
            None => {}
        }
        //drop(ref_to_0);
        //let ref_to_2 = &mut bm[2];
        //bm[0] = None;//this line does NOT work!! Cuz mut borrow `&mut bm[0]` happening already
        //bm[1] = None;//this line also does NOT work!!
        //*ref_to_0 = None;//this line cannot work because it is borrowed
        println!("{:?}", dynamic_r); //you CANNOT print this AFTER dropping bm!! you can only print BEFORE dropping!!

        //println!("{:?}", dynamic_o);
        drop(bm);
        //println!("{:?}", dynamic_r);//this line cannot work!! cuz bm is already dropped!!
        //MUST manually drop bm!!! otherwise you still cannot print r1/r2
        println!("{:?}", r1); //this can prints after bm drops
    }
    println!("END");
}
