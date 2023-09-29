mod foo {
    pub trait Zoo {
        fn zoo(&self) {
            println!("wwww");
        }
    }

    impl<T> Zoo for T {}
}

//use self::foo::Zoo as _;
struct Zoo; // Underscore import avoids name conflict with this item.

fn main() {
    let z = Zoo;
    //z.zoo();
    foo::Zoo::zoo(&z);
}
//note foo::Zoo::zoo(&z); has the same effect as z.zoo();
