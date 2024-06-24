import base64

iv_base64 = "H+xoK8/xdac4YgHtWyN/YQ=="
iv_bytes = base64.b64decode(iv_base64)
print(iv_bytes)

import hashlib

# List of potential keys to test (brute-force, dictionary, etc.)
potential_keys = ["hash","A5cbc","Hash","H+xoK8/xdac4YgHtWyN/YQ=="," hash","Hint: hash","(Hint: hash)","Hint","codenamehackernr"]

# Target hash to match
target_md5 = "d5c25cc61ce78139a545e22c7d220d84"

# Iterate over each potential key
for key in potential_keys:
    # Create MD5 hash of the current key
    md5_hash = hashlib.md5(key.encode()).hexdigest()

    # If the hash matches the target, we've found the correct key
    if md5_hash == target_md5:
        print(f"Match found: {key}")  # This is the original encryption key
        break
    else:
        print(f"{key} :no match")



base64ofbananaimage = "base64:Q6dMPcA7WoyikldkrEV2xuRFsiEXRgmZEDHZSBnzSRjoLZIL04evi9lzD1H5LwK2nQXepRfdOvfruETNQg6mlypE3uEvQckg9DQrCr0R9vw5+WYZT5Yy1kIUMzjLvkOFcx9ziD0BOUnDYUTbbIZT7lIYUOqxC5EtVbRrOmmeG7LbibxxC9w+OrNmOMs64eu32IJpnvWYLtH6cHepm/OzdISJIbEkxq6VFhG7HfW7gXMdnWM73lIRkyFc/X9dQr2Ji0oLulJulOeklLfDTwKRcmed/I3cSwgi4sfo4ny2FAvsn6PQqa63TwLUi9yONRLaYhZdqvPRW9cSdbvNEw0m9EnCr8JZBrr02+xf0GJLHsABSQgj8uGX429qkBKV8sELraDUazhm9znUwjZo57YUjbtoF3WeDXLkdbChKj+Tvk0r7PUHI8M2q0BnO3u4PLGq1Dso356tIMnIAD608Jvxdh08tku/43210XtGOa1uer1rSSVTMG9P7f5UPQ6YFHQwgl5USgWH9RTpKkx2d8m7cKYfYYG4Sed6ias3/WOv10RoGOMfPijLV+gfWeESDELv3eMSQRTri78PzbxBczFx3Q=="

from base64 import b64decode
from Crypto.Cipher import AES
import hashlib

# Given base64 ciphertext
ciphertext_base64 = "Q6dMPcA7WoyikldkrEV2xuRFsiEXRgmZEDHZSBnzSRjoLZIL04evi9lzD1H5LwK2nQXepRfdOvfruETNQg6mlypE3uEvQckg9DQrCr0R9vw5+WYZT5Yy1kIUMzjLvkOFcx9ziD0BOUnDYUTbbIZT7lIYUOqxC5EtVbRrOmmeG7LbibxxC9w+OrNmOMs64eu32IJpnvWYLtH6cHepm/OzdISJIbEkxq6VFhG7HfW7gXMdnWM73lIRkyFc/X9dQr2Ji0oLulJulOeklLfDTwKRcmed/I3cSwgi4sfo4ny2FAvsn6PQqa63TwLUi9yONRLaYhZdqvPRW9cSdbvNEw0m9EnCr8JZBrr02+xf0GJLHsABSQgj8uGX429qkBKV8sELraDUazhm9znUwjZo57YUjbtoF3WeDXLkdbChKj+Tvk0r7PUHI8M2q0BnO3u4PLGq1Dso356tIMnIAD608Jvxdh08tku/43210XtGOa1uer1rSSVTMG9P7f5UPQ6YFHQwgl5USgWH9RTpKkx2d8m7cKYfYYG4Sed6ias3/WOv10RoGOMfPijLV+gfWeESDELv3eMSQRTri78PzbxBczFx3Q=="

# Recovered encryption key
key = "codenamehackernr"


