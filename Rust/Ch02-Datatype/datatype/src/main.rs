fn main() {
    assert_eq!(10_i8 as u16, 10_u16);
    assert_eq!(2525_u16 as i16, 2525_i16);

    assert_eq!(-1_i16 as i32, -1_i32);
    assert_eq!(65535_u16 as i32, 65535_i32);

    //exceed range
    assert_eq!(1000_i16 as u8, 232_u8);
    let x = 1000_i16 as u8;
    println!("{}", x);
    println!("{}", 1000_i16 % 256); //2^8 = 256, 1000 modulo 256 = 232

    //------------------------------------------------

    assert_eq!(10_u8.checked_add(20), Some(30));
    assert_eq!(100_u8.checked_add(200), None);

    assert_eq!(100_u16.wrapping_mul(200), 20000);
    assert_eq!(500_u16.wrapping_mul(500), 53392);

    assert_eq!(500_i16.wrapping_mul(500), -12144);

    assert_eq!(5_i16.wrapping_shl(17), 10);

    assert_eq!(32767_i16.saturating_add(10), 32767);
    assert_eq!((-32767_i16).saturating_sub(10), -32768);

    assert_eq!(255_u8.overflowing_sub(2), (253, false));
    assert_eq!(255_u8.overflowing_add(2), (1, true));

    assert_eq!(5_u16.overflowing_shl(17), (10, true));

    //------------------------------------------------

    assert!((-1. / f32::INFINITY).is_sign_negative());
    assert_eq!(-f32::MIN, f32::MAX);

    assert_eq!(5f32.sqrt() * 5f32.sqrt(), 5.);
    assert_eq!((-1.01f64).floor(), -2.);

    println!("{}", (2.0_f64).sqrt());
    println!("{}", f64::sqrt(2.));

    //------------------------------------------------

    assert_eq!(false as i32, 0);
    assert_eq!(true as i32, 1);

    //------------------------------------------------

    assert_eq!('*' as i32, 42);

    //------------------------------------------------

    let text = "I see the eigenvalue in thine eye";
    let (mut head, mut tail) = text.split_at(21);
    assert_eq!(head, "I see the eigenvalue ");
    assert_eq!(tail, "in thine eye");

    let temp = text.split_at(21);
    head = temp.0;
    tail = temp.1;
    assert_eq!(head, "I see the eigenvalue ");
    assert_eq!(tail, "in thine eye");

}
