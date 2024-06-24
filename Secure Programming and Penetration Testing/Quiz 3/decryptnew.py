from Crypto.Cipher import AES
import base64
import hashlib

# Given values
ciphertext_base64 = "Q6dMPcA7WoyikldkrEV2xuRFsiEXRgmZEDHZSBnzSRjoLZIL04evi9lzD1H5LwK2nQXepRfdOvfruETNQg6mlypE3uEvQckg9DQrCr0R9vw5+WYZT5Yy1kIUMzjLvkOFcx9ziD0BOUnDYUTbbIZT7lIYUOqxC5EtVbRrOmmeG7LbibxxC9w+OrNmOMs64eu32IJpnvWYLtH6cHepm/OzdISJIbEkxq6VFhG7HfW7gXMdnWM73lIRkyFc/X9dQr2Ji0oLulJulOeklLfDTwKRcmed/I3cSwgi4sfo4ny2FAvsn6PQqa63TwLUi9yONRLaYhZdqvPRW9cSdbvNEw0m9EnCr8JZBrr02+xf0GJLHsABSQgj8uGX429qkBKV8sELraDUazhm9znUwjZo57YUjbtoF3WeDXLkdbChKj+Tvk0r7PUHI8M2q0BnO3u4PLGq1Dso356tIMnIAD608Jvxdh08tku/43210XtGOa1uer1rSSVTMG9P7f5UPQ6YFHQwgl5USgWH9RTpKkx2d8m7cKYfYYG4Sed6ias3/WOv10RoGOMfPijLV+gfWeESDELv3eMSQRTri78PzbxBczFx3Q=="
key_hash = "d5c25cc61ce78139a545e22c7d220d84"

# Recovered encryption key
# Since you already have the key, you don't need to recover it.
key = "codenamehackernr"

# Base64 decode the ciphertext
ciphertext = base64.b64decode(ciphertext_base64)

# Decrypt the ciphertext
iv = ciphertext[:AES.block_size]
cipher = AES.new(key.encode(), AES.MODE_CBC, iv)
plaintext = cipher.decrypt(ciphertext[AES.block_size:])

# Remove padding
padding_length = plaintext[-1]
plaintext = plaintext[:-padding_length]

print("plaintext: ",plaintext)
# Compute the SHA256 hash of the plaintext
plaintext_hash = hashlib.sha256(plaintext).hexdigest()

print("SHA256 hash of the plaintext:", plaintext_hash)