# security-verification-for-Qt
目前实现了rsa私钥加密和rsa公钥加密以及des加解密。需要在项目中添加openssl库。

rsa加解密需要先用openssl生成一对公钥和私钥 可以参考我之前写的文章[openssl简要操作](http://bigxiangbaobao.com/blog/2018/04/11/openssl%E7%AE%80%E8%A6%81%E6%93%8D%E4%BD%9C/)
注意公钥和私钥的格式，我直接采用字符串导入，也可以改成文件导入，我已经做了一对放在项目中。

```
-----BEGIN RSA PRIVATE KEY-----
MIIBOQIBAAJBAK10JHtd9ztzpIgoRhwd3V447wrWlan5te3pwLYKSXiwHG+kynQk
IzvfTjs/kXynjPZTZ+bbeJDHkyclc0jKpj0CAwEAAQJAeu/gk5fMDVUvflmdJ3x7
U7bipjnlJe4Y5iFRNzUfUevFVH5WoE+n7t5hJ915bAb3PGCgFWRxOaCQ7khTwacp
gQIhAOAmv78i2JzpE9oZ78X8/fHqvKXFNgxXWGr8YJ7hNz8RAiEAxhlSrg09ahd1
VXmTxnbPKemx9aanLtbOGkB5+ZhQDG0CIFWtOfl6/kTrqhTheQ66Zu6DBNxwBvqs
oDU0hlH0T8OhAiBBocgr1EUhri34qLQWD+zo9P055wIC2bYlKnF/CUCULQIgYUa+
BjdjJuOWyepJx84xwzZjcSEyzCxKpLt46O/7Euc=
-----END RSA PRIVATE KEY-----

```

每一行结束都有一个换行符，不加的话会报错，对应的字符串如下：
```
//QString private_key = "-----BEGIN RSA PRIVATE KEY-----\nMIIBOQIBAAJBAK10JHtd9ztzpIgoRhwd3V447wrWlan5te3pwLYKSXiwHG+kynQk\nIzvfTjs/kXynjPZTZ+bbeJDHkyclc0jKpj0CAwEAAQJAeu/gk5fMDVUvflmdJ3x7\nU7bipjnlJe4Y5iFRNzUfUevFVH5WoE+n7t5hJ915bAb3PGCgFWRxOaCQ7khTwacp\ngQIhAOAmv78i2JzpE9oZ78X8/fHqvKXFNgxXWGr8YJ7hNz8RAiEAxhlSrg09ahd1\nVXmTxnbPKemx9aanLtbOGkB5+ZhQDG0CIFWtOfl6/kTrqhTheQ66Zu6DBNxwBvqs\noDU0hlH0T8OhAiBBocgr1EUhri34qLQWD+zo9P055wIC2bYlKnF/CUCULQIgYUa+\nBjdjJuOWyepJx84xwzZjcSEyzCxKpLt46O/7Euc=\n-----END RSA PRIVATE KEY-----\n";
```

使用很简单
```
    QString text ="xxxxxxx"; //要加密的字符串 
	SecurityVerification security;
	QString des_key = QString("hdsdsdwed667");
	QString dec_str = security.desEncryption(text, des_key);
```
