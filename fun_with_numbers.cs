using System;
using System.Threading;
using System.Threading.Tasks;

namespace FunWithNumbers {
    internal class Program {
        public static ulong NumbersEntered, TotalOfNumbers, AverageOfNumbers, SmallestNumberEntered, LargestNumberEntered, CoordinatesPlotted;
        public static void Main(string[] args) {
            while(true) {
                Console.Clear();
                Console.WriteLine("Welcome to Fun With Numbers");
                Console.WriteLine("Choose from the menu below:");
                Console.WriteLine(" (A) Check number features");
                Console.WriteLine(" (B) Plot numbers");
                Console.WriteLine(" (C) Check overall stats");
                Console.WriteLine();
                Console.WriteLine(" (X) Save and exit");
                Console.Write("Choice: ");
                string choice = Console.ReadLine().ToLower();

                if (choice == "a") {
                    CheckNumberFeatures();
                } else if (choice == "b") {
                    PlotNumbers();
                } else if (choice == "c") {
                    CheckOverallStats();
                } else if (choice == "x") {
                    Environment.Exit(0);
                }
            }
        }

        public static void CheckNumberFeatures() {
            Console.Clear();
            Console.Write("Please enter a whole number that will be checked over: ");
            ulong Number = ulong.Parse(Console.ReadLine());

            // Change and update the variable
            TotalOfNumbers += Number;
            NumbersEntered++;
            AverageOfNumbers = TotalOfNumbers / NumbersEntered;

            if (Number > LargestNumberEntered) {
                LargestNumberEntered = Number;
            } else if (Number < SmallestNumberEntered) {
                SmallestNumberEntered = Number;
            }

            Console.WriteLine();
            Console.WriteLine("The features of {0} are...", Number);

            // Check if number is positive, negative, or zero
            if (Number > 0uL) {
                Console.WriteLine("  Positive");
            } else if (Number < 0uL) {
                Console.WriteLine("  Negative");
            } else {
                Console.WriteLine("  Zero");
            }

            // Check if number is even or odd
            if (Number % 2uL == 0uL) {
                Console.WriteLine("  Even");
            } else {
                Console.WriteLine("  Odd");
            }

            // Print factors and is the number is prime or not
            // bool IsPrime = true;
            Console.Write("  Factors are ");
            CustomParallel(Number);

            // Console.WriteLine("\n  {0}", IsPrime ? "Is a prime number" : "Is not a prime number");

            // Wait for a key being pressed before exiting
            Console.ReadLine();
        }

        public static void PlotNumbers() {
            Console.Clear();
        }

        public static void CheckOverallStats() {
            Console.Clear();
            Console.WriteLine(NumbersEntered);
        }

        static void CustomParallel(ulong Number)
        {
            var degreeOfParallelism = Environment.ProcessorCount;
            // Console.Write(degreeOfParallelism);

            var tasks = new Task[degreeOfParallelism];

            for (int taskNumber = 0; taskNumber < degreeOfParallelism; taskNumber++)
            {
                // capturing taskNumber in lambda wouldn't work correctly
                int taskNumberCopy = taskNumber;

                tasks[taskNumber] = Task.Factory.StartNew(
                    () =>
                    {
                        // Console.Write((ulong)(taskNumberCopy / degreeOfParallelism));
                        for (ulong i = 1uL;
                            i < Number;
                            i++)
                        {
                            if (Number % i == 0uL) {
                                Console.Write(" {0}", i);
                                // if (i == 1uL || i == Number) {
                                //     continue;
                                // } else {
                                //     IsPrime = false;
                                // }
                            }
                        }
                    });
            }

            Task.WaitAll(tasks);
        }
    }
}
