# CPP06

## What is a scalar type

In programming, when we say a scalar type represents a single value, we mean that variables of a scalar type hold one piece of data at a time. This contrasts with compound types, which can hold multiple pieces of data, often of various types, at the same time. Scalar types are the simplest form of data types and serve as the building blocks for more complex data structures.

Scalar types are often considered primitive types. The term "primitive" refers to the basic data types provided by a programming language as built-in types. These are the types that are not built out of other data types but rather serve as the fundamental data types from which more complex types can be constructed.

**Examples of Scalar Types in C++98:**

- `int`: Represents integer numbers.
- `float`: Represents single-precision floating-point numbers.
- `double`: Represents double-precision floating-point numbers.
- `char`: Represents single characters.
- `bool`: Represents boolean values (`true` or `false`).

**Examples of Compound Types in C++98:**

- `arrays`: An array in C++ is a compound type that allows you to store multiple elements of the same type together. For example, `int numbers[5];` defines an array of five integers.
- `struct`: A structure is a user-defined compound type that can encapsulate variables of different types. For example:
  ```cpp
  struct Person {
    std::string name;
    int age;
  };
  ```
- `class`: Similar to `struct`, but with additional features like encapsulation, inheritance, and polymorphism. For example:
  ```cpp
  class MyClass {
  public:
    void myFunction();
  private:
    int myNumber;
  };
  ```

**Why are they called scalar?**

The term "scalar" originates from mathematics, particularly from linear algebra, where it denotes a single number that can scale vectors without changing their direction, only their magnitude. In programming, the term is borrowed to indicate types that represent a single value, akin to how a mathematical scalar is a single numerical value. This distinguishes scalar types from more complex structures that can hold or manipulate multiple values at once. The use of "scalar" emphasizes the simplicity and singularity of these types in contrast to compound or composite types that can aggregate or structure multiple data items.

**Are scalar types always primitive types?**

In some programming languages, there are primitive types that are not strictly scalar if we adhere to the definition of scalar types representing a single value. JavaScript is a notable example where this distinction becomes interesting.

In JavaScript, a `string` is considered a primitive type. Primitive types in JavaScript are data that is not an object and has no methods. There are 7 primitive data types: `string`, `number`, `bigint`, `boolean`, `undefined`, `symbol`, and `null`. However, unlike other scalar types such as `number` or `boolean`, which indeed hold a single value (like a single numerical value or a true/false value), a `string` can represent multiple characters grouped together as a single entity. For example, `"Hello, world!"` is a string primitive that contains multiple characters.

This might seem to blur the line between scalar and compound types because a string can hold multiple characters. However, in the context of JavaScript and many other programming languages, strings are still considered scalar or primitive because they are treated as single, immutable values. Even though a string can contain many characters, you interact with it as a whole. You can't change individual characters in the string directly (immutable) without creating a new string.

The key point is that the classification of types as scalar, primitive, or compound can vary slightly between programming languages based on how those types are implemented and manipulated. In JavaScript, `string` is indeed a primitive type because it meets the criteria of being immutable and directly representable at the lowest level of the language, despite it conceptually holding multiple characters.
