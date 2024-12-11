using System;

public class Money
{
    public int Grivns{ get; private set; }
    public int Kopeecks{ get; private set; }

        public Money(int grivns, int kopeecks)
    {
        if (grivns < 0 || kopeecks < 0)
        {
            throw new InvalidOperationException("Cannot create an object with a negative amount.");
        }

        Grivns = grivns;
        Kopeecks = kopeecks;
        Normalize();
    }

    private void Normalize()
    {
        if (Kopeecks >= 100)
        {
            Grivns += Kopeecks / 100;
            Kopeecks %= 100;
        }
    }

    public static Money operator +(Money a, Money b)
    {
        return new Money(a.Grivns + b.Grivns, a.Kopeecks + b.Kopeecks);
    }

    public static Money operator -(Money a, Money b)
    {
        int totalKopecksA = a.Grivns * 100 + a.Kopeecks;
        int totalKopecksB = b.Grivns * 100 + b.Kopeecks;

        if (totalKopecksA < totalKopecksB)
        {
            throw new InvalidOperationException("Bankrupt");
        }

        return new Money((totalKopecksA - totalKopecksB) / 100, (totalKopecksA - totalKopecksB) % 100);
    }

    public static Money operator *(Money a, int multiplier)
    {
        if (multiplier < 0)
        {
            throw new InvalidOperationException("Cannot multiply by a negative number.");
        }
        return new Money(a.Grivns * multiplier, a.Kopeecks * multiplier);
    }

    public static Money operator /(Money a, int divisor)
    {
        if (divisor <= 0)
        {
            throw new InvalidOperationException("Cannot divide by zero or a negative number.");
        }
        int totalKopecks = a.Grivns * 100 + a.Kopeecks;
        return new Money(totalKopecks / divisor / 100, (totalKopecks / divisor) % 100);
    }

    public static Money operator ++(Money a)
    {
        return new Money(a.Grivns, a.Kopeecks + 1);
    }

    public static Money operator --(Money a)
    {
        if (a.Grivns == 0 && a.Kopeecks == 0)
        {
            throw new InvalidOperationException("Bankrupt");
        }
        return new Money(a.Grivns, a.Kopeecks - 1);
    }

    public static bool operator <(Money a, Money b)
    {
        return (a.Grivns * 100 + a.Kopeecks) < (b.Grivns * 100 + b.Kopeecks);
    }

    public static bool operator >(Money a, Money b)
    {
        return (a.Grivns * 100 + a.Kopeecks) > (b.Grivns * 100 + b.Kopeecks);
    }

    public static bool operator ==(Money a, Money b)
    {
        return (a.Grivns * 100 + a.Kopeecks) == (b.Grivns * 100 + b.Kopeecks);
    }

    public static bool operator !=(Money a, Money b)
    {
        return (a.Grivns * 100 + a.Kopeecks) != (b.Grivns * 100 + b.Kopeecks);
    }

    public override bool Equals(object obj)
    {
        if (obj is Money)
        {
            Money other = (Money)obj;
            return this == other;
        }
        return false;
    }

    public override int GetHashCode()
    {
        return (Grivns * 100 + Kopeecks).GetHashCode();
    }

    public static void Main(string[] args)
    {
        try
        {
            Money m1 = new Money(15, 30);
            Money m2 = new Money(8, 85);

            Money sum = m1 + m2;
            Console.WriteLine($"Sum: {sum.Grivns} grivens, {sum.Kopeecks} kopecks");

            Money diff = m1 - m2;
            Console.WriteLine($"Difference: {diff.Grivns} grivens, {diff.Kopeecks} kopecks");

            Money product = m1 * 2;
            Console.WriteLine($"Product: {product.Grivns} grivens, {product.Kopeecks} kopecks");

            Money quotient = m1 / 2;
            Console.WriteLine($"Quotient: {quotient.Grivns} grivens, {quotient.Kopeecks} kopecks");

            m1++;
            Console.WriteLine($"Incremented: {m1.Grivns} grivens, {m1.Kopeecks} kopecks");

            m2--;
            Console.WriteLine($"Decremented: {m2.Grivns} grivens, {m2.Kopeecks} kopecks");

            bool isEqual = m1 == m2;
            Console.WriteLine($"Equal: {isEqual}");

            bool isNotEqual = m1 != m2;
            Console.WriteLine($"Not equal: {isNotEqual}");

            bool isLess = m1 < m2;
            Console.WriteLine($"Less: {isLess}");

            bool isGreater = m1 > m2;
            Console.WriteLine($"Greater: {isGreater}");
        }
        catch (Exception e)
        {
            Console.WriteLine(e.Message);
        }
    }
}
