fn main() {
    let mut v = Vec::<u8>::new();
    v.push(0x41);
    v.push(0x42);
    v.push(0x43);
    let sli = &v[..];
    println!("{}", String::from_utf8_lossy(sli));
    println!("{}", sli.get(3..).unwrap().len());
    println!("{}", sli.get(3..).is_some());//this prints true
}
