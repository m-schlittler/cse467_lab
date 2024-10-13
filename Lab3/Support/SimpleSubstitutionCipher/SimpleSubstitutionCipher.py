def main():
    key, msg = prompt()
    enc = ''
    dec = ''

    for c in msg:
        enc += encrypt(c, key)

    for c in enc:
        dec += decrypt(c, key)

    print(f"Key: {key}")
    print(f"MSG: {msg}")
    print(f"ENC: {enc}")
    print(f"DEC: {dec}")

def prompt() -> tuple[int, str]:
    key = input("Key (Enter nothing for default) = ")
    if key is None or key == '':
        key = 4
    else:
        key = int(key)

    msg = input("Message (Enter nothing for default) = ")
    if msg is None or msg == '':
        msg = "I AM ENGINEERING STUDENT AT WASH U"

    return key, msg

def encrypt(c: str, key: int) -> str:
    NUM_CHARS = 27
    BASE = ord('A')

    x = 26 if c == ' ' else ord(c) - BASE

    x = (x + key) % NUM_CHARS

    return '_' if x == 26 else chr(x + BASE)

def decrypt(c: str, key: int) -> str:
    NUM_CHARS = 27
    BASE = ord('A')
    
    x = 26 if c == '_' else ord(c) - BASE

    x = (x + NUM_CHARS - key) % NUM_CHARS

    return ' ' if x == 26 else chr(x + BASE)

if __name__ == "__main__":
    main()