const int NUM_CHARS = 27;


PromptInput(out byte key, out string msg);
string enc = string.Empty;
string dec = string.Empty;

for (int i = 0; i < msg.Length; i++)
{
    enc += Encrypt(msg[i], key);
}

for (int i = 0; i < msg.Length; i++)
{
    dec += Decrypt(enc[i], key);
}

Console.WriteLine($"Key: {key}");
Console.WriteLine($"MSG: {msg}");
Console.WriteLine($"ENC: {enc}");
Console.WriteLine($"DEC: {dec}");

Console.WriteLine();
Console.WriteLine("Press Enter to exit...");
Console.ReadLine();

void PromptInput(out byte key, out string msg)
{
    string? temp;
    Console.Write("Key (Enter nothing for default) = ");
    temp = Console.ReadLine();
    if (!byte.TryParse(temp, out key))
    {
        key = 4;
    }

    Console.WriteLine("Message (Enter nothing for default) = ");
    temp = Console.ReadLine();
    msg = string.IsNullOrEmpty(temp) ? "I AM ENGINEERING STUDENT AT WASH U" : temp;
}

char Encrypt(char c, byte key)
{
    const byte numChars = 27;
    byte x = (byte)(c == ' ' || c == '_' ? 26 : (c - 'A'));

    x = (byte)((x + key) % numChars);

    return (char)(x == 26 ? '_' : x + 'A');
}

char Decrypt(char c, int key)
{
    const byte numChars = 27;
    byte x = (byte)(c == '_' ? 26 : (c - 'A'));

    x = (byte)((x + numChars - key) % numChars);

    return (char)(x == 26 ? ' ' : x + 'A');
}