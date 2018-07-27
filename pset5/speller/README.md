# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

a synonym for the disease known as silicosis.

## According to its man page, what does `getrusage` do?

get resource usage.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

To save memory

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

Until the end of the file, the for loop in main gets a new character from the file. If the character is alphabetic or an apostrophe, it is appended to the current word, and if the word becomes too large it is ignored and the rest of the word is skipped. If the character is a digit, the current word is ignored and the rest of it is skipped. If the first two conditions are false and the word is not empty, the word has been found and it is checked.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

Using fscanf would make it more difficult to check each character.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

The value of those paramaters are const because they should not be changed.
