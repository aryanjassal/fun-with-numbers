using System;
// using System.Collections.Generic;

namespace FunWithNumbers {
	class Program {
		static void Main(string[] args) {
			while (true) {
				Console.Clear();
				Console.WriteLine("Welcome to Fun With Numbers");
				Console.WriteLine("Choose from the menu below:");
				Console.WriteLine(" (A) Check number features");
				Console.WriteLine(" (B) Plot numbers");
				Console.WriteLine(" (C) Check overall stats");
				Console.WriteLine();
				Console.WriteLine(" (X) Save and exit");
				Console.Write("Choice: ");
				string choice = Console.ReadLine();
			
				if (choice.ToLower() == "a") {
					CheckNumberFeatures();
				} else if (choice.ToLower() == "b") {
					PlotNumbers();
				} else if (choice.ToLower() == "c") {
					CheckOverallStats();
				} else if (choice.ToLower() == "x") {
					Environment.Exit(0);
				}
			}
		}

		static void CheckNumberFeatures() {
			Console.Clear();
			Console.Write("Please enter a whole number that will be checked over: ");
			int number = Int32.Parse(Console.ReadLine());
			
			Console.WriteLine();
			Console.WriteLine("The features of {0} are...", number);

			// Check if number is positive, negative, or zero
			if (number > 0) {
				Console.WriteLine("  Positive");
			} else if (number < 0) {
				Console.WriteLine("  Negative");
			} else {
				Console.WriteLine("  Zero");
			}

			// Check if number is even or odd
			if (number % 2 == 0) {
				Console.WriteLine("  Even");
			} else {
				Console.WriteLine("  Odd");
			}

			// Calculate factors and if the number is prime or not
			bool prime = true;
			Console.Write("  Factors are");
			for (int i = 1; i <= number; i++) {
				if (number % i == 0) {
					Console.Write(" {0}", i);
					if (i == 1 || i == number) {
						continue;
					} else {
						prime = false;
					}
				}
			}
			Console.WriteLine("\n  {0}", prime ? "Is a prime number" : "Is not a prime number");
			
			// Wait for key
			Console.ReadLine();
		}

		static void PlotNumbers() {
			Console.Clear();
		}

		static void CheckOverallStats() {
			Console.Clear();
		}
	}
}
