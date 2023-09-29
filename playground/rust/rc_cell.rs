use std::cell::*;
use std::rc::*;

fn print_type_of<T>(_: &T) {
    println!("{}", std::any::type_name::<T>())
}

fn main() {
    {
        let mut c1 = Cell::new(vec![1, 2]);
        c1.get_mut().push(3);
        println!("{:?}", c1.into_inner());
    }
    {
        let c2 = Cell::new(vec![1, 2]);
        c2.set(vec![3, 4]);
        println!("{:?}", c2.into_inner());
        //OMG Cell allows changing value even though it is NOT `mut`!!!
    }
    //OMG Cell has no method to provide immutable reference to inner data!!! It is a very interesting trade-off here: with the privilege of mutating inner data granted to Cell, it loses the ability of emitting mere immutable reference. To gain something valuable, you must lose something valuable.
    {
        let l_rc1: Rc<Cell<i32>> = Rc::new(Cell::new(1));
        let l_rc2 = Rc::clone(&l_rc1);
        println!("{:?}", *l_rc1);
        println!("{:?}", *l_rc2);
        (*l_rc1).set(2);
        println!("{:?}", *l_rc2);
        println!("{:?}", *l_rc1);
    }
    {
        //let l_rc3: Rc<i32> = Rc::new(3);
        //let l_rc4 = Rc::clone(&l_rc3);
        let v1 = vec![1, 2, 3, 4];
        print_type_of(&v1);
        //let l_rcv1 = Rc::new(Cell::new(v1));
        let mut l_rcv1 = Rc::new(Cell::new(v1));
        let mut l_rcv2 = Rc::clone(&l_rcv1);
        //let mut l_rcv1 = Box::new(v1);
        //let l_rcv2 = Rc::clone(&l_rcv1);
        let outv = (*l_rcv1).replace(vec![1, 2]);
        //(*l_rcv1).borrow_mut().push(5);
        println!("{:?}", outv);
        let outv2 = (*l_rcv2).replace(outv);
        println!("{:?}", outv2);
        //println!("{:?}", (*l_rcv2).into_inner());
        //println!("{:?}", *l_rcv1);
    }
    println!("END");
}
