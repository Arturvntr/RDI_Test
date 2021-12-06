using System;
using System.Numerics;

public class Palindrome
{
	/* Function to check if a given string can be a palidrome permuting its letters
	*  @param: text - String to be checked
	*	string must contain lowcaser letters between a - z
	*   Function check if there is more than one letters with odd amount. if there is this text cannot be a palindrome
	*/
	public string isPalindromePermutaiton(string text)
	{
		int[] letters = new int[27];

		for (int i = 0; i < text.Length; i++)
		{
			var iChar = text[i] - 'a';
			letters[iChar]++;
		}

		var isPalindrome = true;
		var oddCount = 0;
		for (int i = 0; i < letters.Length && isPalindrome; i++)
		{
			if (letters[i] % 2 != 0) oddCount++;
			if (oddCount > 1) isPalindrome = false;
		}

		return (isPalindrome ? "YES" : "NO");

	}

	public static void Main()
	{
		Palindrome palindrome = new Palindrome();

		string value, result, compare, testNumber, print;

		// Test 1
		testNumber = "Test 1";
		value = "a";
		compare = "YES";
		result = palindrome.isPalindromePermutaiton(value);
		if (result == compare) print = testNumber + " Pass     -     " + result + "\n";
		else print = testNumber + " Fail     -     " + result + "\n";
		Console.WriteLine(print);

		// Test 2
		testNumber = "Test 2";
		value = "ab";
		compare = "NO";
		result = palindrome.isPalindromePermutaiton(value);
		if (result == compare) print = testNumber + " Pass     -     " + result + "\n";
		else print = testNumber + " Fail     -     " + result + "\n";
		Console.WriteLine(print);

		// Test 3
		testNumber = "Test 3";
		value = "carroaco";
		compare = "YES";
		result = palindrome.isPalindromePermutaiton(value);
		if (result == compare) print = testNumber + " Pass     -     " + result + "\n";
		else print = testNumber + " Fail     -     " + result + "\n";
		Console.WriteLine(print);

		// Test 4
		testNumber = "Test 4";
		value = "abcabcabc";
		compare = "NO";
		result = palindrome.isPalindromePermutaiton(value);
		if (result == compare) print = testNumber + " Pass     -     " + result + "\n";
		else print = testNumber + " Fail     -     " + result + "\n";
		Console.WriteLine(print);

		// Test 5
		testNumber = "Test 5";
		value = "abcabcabczc";
		compare = "NO";
		result = palindrome.isPalindromePermutaiton(value);
		if (result == compare) print = testNumber + " Pass     -     " + result + "\n";
		else print = testNumber + " Fail     -     " + result + "\n";
		Console.WriteLine(print);

		// Test 6
		testNumber = "Test 6";
		value = "abcabcabcca";
		compare = "YES";
		result = palindrome.isPalindromePermutaiton(value);
		if (result == compare) print = testNumber + " Pass     -     " + result + "\n";
		else print = testNumber + " Fail     -     " + result + "\n";
		Console.WriteLine(print);
	}
}

