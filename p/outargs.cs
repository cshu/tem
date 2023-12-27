using System;

namespace HelloWorld
{
    class Hello
    {
        static void Main(string[] args)
        {
	    foreach(var arg in args){
                Console.WriteLine(arg);
                Console.WriteLine("\n\n");
	    }
        }
    }
}
