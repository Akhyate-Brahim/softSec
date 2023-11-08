# Cryptography Lab 1

## Frequency analysis of a substitution encryption

```bash
$ tr 'ytnvupmrqbdxzahlcgeifskjo' 'THEANDIGSFYOUCRWMBPLVKXQJ' <ciphertext.txt> test.txt 
```

[./Labsetup/Files/ciphertext.txt](ciphertext) -> [./Labsetup/Files/test.txt](plaintext)

## ECB AND CBC MODES ON PICS

ECB BAD
CBC GOOD BUT SLOW

## Padding

- ECB and CBC: Require padding because they work on fixed-size blocks. If the last block is incomplete, it's padded.

- CFB and OFB: Don't require padding because they operate like stream ciphers, handling data of any size without needing full blocks.

- The padding scheme used is PKCS#7, where each of the N padding bytes is set to the value N.

- For data that's already an exact multiple of the block size, a full block of padding is added, and each byte in this padding block is set to the block size itself (e.g., for a 16-byte block, 16 bytes of '10' in hex are added).*

## propagation of error in certain modes

ECB (Electronic Codebook): Corruption in one block only affects that block. The rest can be decrypted normally.

CBC (Cipher Block Chaining): A corrupted block will mess up its own decryption and that of the entire next block.

CFB (Cipher Feedback): A bit error in one block affects the corresponding bit in the next block, but then stops affecting subsequent bits.

OFB (Output Feedback): A corrupted block only affects itself; the rest of the data can be decrypted normally.

## initial vector

- using the same initial vector results in the same encrypted file, thus the same file will always be encrypted in the same way which is not ideal.

```bash
[10/25/23]seed@VM:~/.../initial_vector$ hexdump -C out.txt
00000000  1d dd 53 e1 0f 13 5b cd  d6 a0 36 69 03 db ad 53  |..S...[...6i...S|
00000010
[10/25/23]seed@VM:~/.../initial_vector$ hexdump -C out2.txt
00000000  1d dd 53 e1 0f 13 5b cd  d6 a0 36 69 03 db ad 53  |..S...[...6i...S|
00000010
```

when using a different iv: 
```bash
[10/25/23]seed@VM:~/.../initial_vector$ hexdump -C out3.txt
00000000  2d 83 9e 30 83 e9 88 34  21 6f 89 ff 70 ae 94 e8  |-..0...4!o..p...|
00000010
```
