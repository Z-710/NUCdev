
def mult(a,b):
    return a*b


if __name__ == "__main__":
    print("Enter a number: ", end="")
    a = int(input())
    print("Enter another number: ", end="")
    b = int(input())
    print(str(a) +" x "+ str(b) + " = " + str(mult(a, b)))
