C = 36079330327544751883336873492619252
e = 65537
n = 764721720347891218098402268606191971
phi_n = 764721720347891216342750510363821392
d = 487033582336704937347300968187062897

# Check if d * e is congruent to 1 modulo phi(n)
if (d * e) % phi_n == 1:
    # Compute the plaintext
    plaintext = pow(C, d, n)
    print("Plaintext:", plaintext)
else:
    print("Error: d * e is not congruent to 1 modulo phi(n)")