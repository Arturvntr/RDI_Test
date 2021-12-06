using System.Numerics;

public class Palindrome
{

	public string isPalindromePermutaiton(string text)
    {
        //var letters = Vector.Create<int>(27);
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

		string temp = "abcabcabcabczz";

		string result = palindrome.isPalindromePermutaiton(temp);

		Console.WriteLine(result);

	}
}

