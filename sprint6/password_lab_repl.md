# Password Cracking

During your readings (sections 10.2 and 10.3), you learned about how the operating system is responsible for **user authentication** (verifying the identity of the person attempting to use the computer) as well as **access control** (verifying that a user can or cannot access specific files or applications).  In modern systems, unique user passwords are the first line of authentication and control. In this lab, we'll work on cracking some passwords using *John the Ripper*, an open source cracking program.  We'll also explore the concepts of *hashing* and *salting* in a modern operating system.

## Before We Begin:
You should never try to crack someone else's password.  It's unethical and illegal.  That said, there is great educational value in understanding how passwords are stored and what makes a good, secure password.  Lack of strong passwords and good password security is, literally, a national security-level issue.  As a soon-to-be "expert" (seriously, you'll be amazed at the questions you get asked when someone discovers you have a degree in computer science), you **MUST** understand password security.  

The tool included in this lab, John the Ripper, is an open-source tool which is often used by systems administrators to detect weak user passwords.  It's an important tool for penetration testers, ethical hackers, network administrators, security consultants, forensic staff, security software vendors, and other security professionals.

At the end of this lab, you should have a much better understanding of:
1. what makes a secure password
2. how easy it is to crack weak passwords
3. how hashing algorithms and salting combine for secure password storage


## Background Information: 

### How does a Linux system store your password?

Old systems actually stored users' passwords in a cleartext file called `/etc/passwd`. Unfortunately, this meant that anyone gaining access to that file would have every system users' real password.

Modern systems use a **shadow** password file, stored in `/etc/shadow`. The shadow file doesn't store user's real passwords. Instead, it stores **hashes** of each password.

Recall: **what's a hash function**?

When a user logs in, the system can calculate the hash of the user password and compares it to the stored hash in the shadow file. If the hashes match, then the system assumes that the submitted password is the real password and accept the user's credentials.

Note that for this to be secure, it must be **impossible** to recover the real password given only the hash in the shadow file. Strong cryptographic hash functions have this property. In practice, however, weak passwords may still be easy to crack.

Try to dump the contents of `/etc/shadow/` to the screen using the `cat` command.  

```
prompt$ cat /etc/shadow
```

As you might expect, the `shadow` file contains sensitive information, so it's not accessible to regular users. You have to use root-level priviliges to interact with it.

XXX place sample file here for exploration

Look for a line that begins with `student:$6$zpU...`. This is shadow password file entry for user `student`, the user account we just created.

The huge string specifies the hash of `student`'s password. In this case, we know the password is `raspberry`, but it would be hard to determine that if all we had was the `shadow` file.

The leading `$6$` at the beginning of the hash string is called the **salt**. The number in the salt identifies the function used to generate the hashed password entry. The value 6 indicates the SHA-512 hash function.


### How can passwords be cracked?

A password cracker takes a shadow password file as input and reverse-engineers the real passwords that correspond to the hashes it contains.  It hashes candidate (potential) passwords and then compares the generated hash against the hash in the shadow file.  If the hashes match, the password has been found.  *Sidenote: this is why it's very important that hashing algorithms used in cryptography generate very few **collisions** - different character sequences which have the same hash.*

Now let's make an example shadow password file:

```
prompt$ openssl passwd -1 "password" > shadow_test
```

`openssl` is a program for performing, among other things, crypto-related operations. The `-1` flag indicates the MD5 hash function. `password` is the real password that is being hashed.

The operation `> shadow_test` redirects the output of `openssl`, which would normally be printed to the terminal, to a file named `shadow_test`. You can check the contents of the file:

```
prompt$ cat shadow_test
```

## Part 1: Get cracking

Let's try to use `john` to find the password we just hashed:

```
prompt$ john shadow_test
```

John quickly tries a few basic cracking rules, one of which is blasting through a list of common passwords. Since `password` is on that list, it quickly identifies that the string `password` matches up with the data in the `shadow_test` file.

Let's try something a littler harder and make the password a less common word like `raspberry` instead:

```
prompt$ openssl passwd -1 "raspberry" > shadow_test
```

You can run `john shadow_test` again and let it run for a minute or so, but it won't crack the password. `raspberry` is too unusual for the default cracking approach. 

**Question 1**: Press the spacebar 3-5 times as `john` runs to get a status update on what it's currently trying (look at the end of the line).  Copy/Paste your output to your report.

**Question 2**: As stated earlier, the `-1` flag uses the MD5 hashing algorithm.  Use Google to determine the security of this algorithm. (Include your sources).  Would you choose to use the MD5 algorithm as a systems administrator?

Press `Ctl-C` to exit `john` if it has not already finished.

## Part 2: Dictionary Attacks

Can we do better? Yes, we can, with a **dictionary** attack.  In dictionary attacks, we try each word/sequence in a very large list of potential passwords. I've provided a file with a list of 400,000 English words: `words_alpha.txt`.  (For comparison, research shows that the average 20 year old knows about 42,000 words, so our file contains a sizeable list.)  Sidenote: don't think that you can get around this sort of attack by using foreign words.  Turns out, dictionaries exist in every language.

Now run the program again, using the dictionary file as a list of candidate passwords.

```
prompt$ john --wordlist=words_alpha.txt shadow_test
```

**Question 3**: As before, press the spacebar 3-5 times for updates as it cracks (before it finds the password) and copy/paste the output to your report.

It will take about 20 seconds, but `john` will eventually work its way through the list to find `raspberry` and crack the password. 

## Part 3: Mangling

How about one more?  Many people simply add numbers to the end of a word or change capitalization to meet password requirements.

```
prompt$ openssl passwd -1 "raspberry1" > shadow_test
```

John is still one step ahead of you, because it can apply **mangling rules** to the candidate wordlist to generate new passwords that match common patterns.  Let's see how long it takes to crack our password:

```
prompt$ date;john --wordlist=words_alpha.txt --rules shadow_test;date
```

This approach is extremely effective. People are not very creative, on average, so a good list of words and a set of common mangling patterns is enough to crack a large fraction of the hashes in a typical password database.

**Question 4:** Press space a few times while the program runs.  What sort of mangling rules do you see `john` trying?  Copy and paste output which helps you identify at least 3 suspected mangling rules.

**Question 5:** The `date` command causes Linux to print the system date and time in a format like: `Wed Feb 21 14:51:02 UTC 2020`.  By putting `date;` before and after the `john` command, Linux will print the system time, run `john` and then print the system time again when `john` finishes.  How much time did it take `john` to crack the mangled password?


## Summary: 

How to create good passwords? Basically, a combination of length and unusualness.

- Long, truly random passwords are always strong, because they can only be cracked by brute force. On the other hand, they're almost impossible to remember without a password manager.
    
- Failing that, a combination of length, a large character set with capitals and special characters, and a generation process that avoids common mangling rules.

One popular approach is to randomly string together words from a list.

![xkcd 936](https://imgs.xkcd.com/comics/password_strength.png)

And for further reading, [here's a great explanation](https://explainxkcd.com/wiki/index.php/936:_Password_Strength) of the mathematics of this method.  Is it the strongest password scheme you can use?  No.  But it's a good tradeoff between the usability of the password (your ability to remember it) and the security of the password.
