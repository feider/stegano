# Stegano

A small program to hide information in images.

To embed information into an image, run:

```
echo secret | ./stegano_embed in.bmp out.bmp
```

To get it back out:

```
./stegano_extract out.bmp
```

More implementation details are in the tutorials folder or on [my website](https://www.feider.space/articles/en/steganotut.html)
