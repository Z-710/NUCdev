from base64 import b64decode
from Crypto.Cipher import AES
import hashlib

# Base64 encoded IV and ciphertext
iv = b64decode("H+xoK8/xdac4YgHtWyN/YQ==")
ciphertext_base64 = "Q6dMPcA7WoyikldkrEV2xuRFsiEXRgmZEDHZSBnzSRjoLZIL04evi9lzD1H5LwK2nQXepRfdOvfruETNQg6mlypE3uEvQckg9DQrCr0R9vw5+WYZT5Yy1kIUMzjLvkOFcx9ziD0BOUnDYUTbbIZT7lIYUOqxC5EtVbRrOmmeG7LbibxxC9w+OrNmOMs64eu32IJpnvWYLtH6cHepm/OzdISJIbEkxq6VFhG7HfW7gXMdnWM73lIRkyFc/X9dQr2Ji0oLulJulOeklLfDTwKRcmed/I3cSwgi4sfo4ny2FAvsn6PQqa63TwLUi9yONRLaYhZdqvPRW9cSdbvNEw0m9EnCr8JZBrr02+xf0GJLHsABSQgj8uGX429qkBKV8sELraDUazhm9znUwjZo57YUjbtoF3WeDXLkdbChKj+Tvk0r7PUHI8M2q0BnO3u4PLGq1Dso356tIMnIAD608Jvxdh08tku/43210XtGOa1uer1rSSVTMG9P7f5UPQ6YFHQwgl5USgWH9RTpKkx2d8m7cKYfYYG4Sed6ias3/WOv10RoGOMfPijLV+gfWeESDELv3eMSQRTri78PzbxBczFx3Q=="

# Encryption key
key = "codenamehackernr"

# Decode ciphertext
ciphertext = b64decode(ciphertext_base64)

# Decrypt with CBC
cipher = AES.new(hashlib.md5(key.encode()).digest(), AES.MODE_CBC, iv)

# Get decrypted data and remove padding
decrypted_data = cipher.decrypt(ciphertext)

# Function to handle padding removal
def remove_padding(data):
    padding_length = data[-1]
    if padding_length <= 16:
        return data[:-padding_length]
    return data

# Correctly trimmed plaintext
plaintext = remove_padding(decrypted_data)

# Decode with 'latin-1' if UTF-8 raises errors
try:
    decoded_plaintext = plaintext.decode('utf-8')
except UnicodeDecodeError:
    decoded_plaintext = plaintext.decode('latin-1')

# Calculate the SHA256 hash
sha256_hash = hashlib.sha256(decoded_plaintext.encode()).hexdigest()

print("SHA256 hash of the decrypted plaintext:", sha256_hash)
