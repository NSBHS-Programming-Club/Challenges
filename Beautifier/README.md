# Challenge:

You must create a Java (or any C-like language) "beautifier" that turns code like this:

```java
public class Permuter {
    private static void permute(int n, char[] a) {
        if (n == 0) {
            System.out.println(String.valueOf(a));
        } else {
            for (int i = 0; i <= n; i++) {
                permute(n-1, a);
                swap(a, n % 2 == 0 ? i : 0, n);
            }
        }
    }

    private static void swap(char[] a, int i, int j) {
        char saved = a[i];
        a[i] = a[j];
        a[j] = saved;
    }
}
```

into this:

```java
public class Permuter                                {
    private static void permute(int n, char[] a)     {
        if (n == 0)                                  {
            System.out.println(String.valueOf(a))    ;}
        else                                         {
            for (int i = 0; i <= n; i++)             {
                permute(n-1, a)                      ;
                swap(a, n % 2 == 0 ? i : 0, n)       ;}}}
    private static void swap(char[] a, int i, int j) {
        char saved = a[i]                            ;
        a[i] = a[j]                                  ;
        a[j] = saved                                 ;}}
```

# Specifications:

Your program must:
- move these characters to the "edge": `;{}`
- make sure that the moved characters are aligned with each other, like in the example

# Extra challenges:

- Make the amount of spaces between the code and the removed characters variable.
- Design a new "beautifier" scheme for other types of languages, not just C-like ones.
