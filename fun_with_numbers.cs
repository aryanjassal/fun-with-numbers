using System;

namespace FunWithNumbers {
    internal class Program {
        public static int NumbersEntered, TotalOfNumbers, AverageOfNumbers, SmallestNumberEntered, LargestNumberEntered, CoordinatesPlotted;
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
            int Number = Int32.Parse(Console.ReadLine());

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
            if (Number > 0) {
                Console.WriteLine("  Positive");
            } else if (Number < 0) {
                Console.WriteLine("  Negative");
            } else {
                Console.WriteLine("  Zero");
            }

            // Check if number is even or odd
            if (Number % 2 == 0) {
                Console.WriteLine("  Even");
            } else {
                Console.WriteLine("  Odd");
            }

            // Print factors and is the number is prime or not
            bool IsPrime = true;
            Console.Write("  Factors are ");
            for (int i = 1; i <= Number; i++) {
                if (Number % i == 0) {
                    Console.Write(" {0}", i);
                    if (i == 1 || i == Number) {
                        continue;
                    } else {
                        IsPrime = false;
                    }
                }
            }

            Console.WriteLine("\n  {0}", IsPrime ? "Is a prime number" : "Is not a prime number");

            // Wait for a key being pressed before exiting
            Console.ReadLine();
        }

        public static void PlotNumbers() {
            Console.Clear();
        }

        public static void CheckOverallStats() {
            Console.Clear();
        }
    }
}
