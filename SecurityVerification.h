#pragma once
#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <openssl/rsa.h>
#include <openssl/des.h>
#include <openssl/pem.h>
#include <openssl/bn.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/ssl.h>
#include "openssl/err.h"

enum
{
	KEY_PUBLIC,
	KEY_PRIVATE,
};

class SecurityVerification
{
public:
	SecurityVerification();
	~SecurityVerification();
	QString rsaEncryption(QString &data, QString &keystr);
	QString rsaDecryption(QString &data, QString &keystr);
	QString desEncryption(QString &data, QString &keystr);
	QString desDecryption(QString &data, QString &keystr);
private:
	RSA *rsaCreate(unsigned char * key, int publi);
};



//QString private_key = "-----BEGIN RSA PRIVATE KEY-----\nMGICAQACEQDQ8GHdtwSVnsg+Lnlv7sJ/AgMBAAECEAWKem3wzpRRJ2WY1AAj03EC\nCQDrGXrEisx3KwIJAOODhvztaHf9AgkAm/XnL4M0aMkCCBXdG+nOfs2ZAghLDkJK\nSKSpAw==\n-----END RSA PRIVATE KEY-----\n";
//QString public_key = "-----BEGIN PUBLIC KEY-----\nMCwwDQYJKoZIhvcNAQEBBQADGwAwGAIRANDwYd23BJWeyD4ueW/uwn8CAwEAAQ==\n-----END PUBLIC KEY-----\n";

//QString private_key = "-----BEGIN RSA PRIVATE KEY-----\nMIIBOQIBAAJBAK10JHtd9ztzpIgoRhwd3V447wrWlan5te3pwLYKSXiwHG+kynQk\nIzvfTjs/kXynjPZTZ+bbeJDHkyclc0jKpj0CAwEAAQJAeu/gk5fMDVUvflmdJ3x7\nU7bipjnlJe4Y5iFRNzUfUevFVH5WoE+n7t5hJ915bAb3PGCgFWRxOaCQ7khTwacp\ngQIhAOAmv78i2JzpE9oZ78X8/fHqvKXFNgxXWGr8YJ7hNz8RAiEAxhlSrg09ahd1\nVXmTxnbPKemx9aanLtbOGkB5+ZhQDG0CIFWtOfl6/kTrqhTheQ66Zu6DBNxwBvqs\noDU0hlH0T8OhAiBBocgr1EUhri34qLQWD+zo9P055wIC2bYlKnF/CUCULQIgYUa+\nBjdjJuOWyepJx84xwzZjcSEyzCxKpLt46O/7Euc=\n-----END RSA PRIVATE KEY-----\n";
//QString public_key = "-----BEGIN PUBLIC KEY-----\nMFwwDQYJKoZIhvcNAQEBBQADSwAwSAJBAK10JHtd9ztzpIgoRhwd3V447wrWlan5\nte3pwLYKSXiwHG+kynQkIzvfTjs/kXynjPZTZ+bbeJDHkyclc0jKpj0CAwEAAQ==\n-----END PUBLIC KEY-----\n";