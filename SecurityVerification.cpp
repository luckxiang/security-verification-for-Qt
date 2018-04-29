#include "SecurityVerification.h"



SecurityVerification::SecurityVerification()
{
}


SecurityVerification::~SecurityVerification()
{
}

RSA * SecurityVerification::rsaCreate(unsigned char * key, int publi)
{
	RSA *rsa = NULL;
	BIO *keybio;
	keybio = BIO_new_mem_buf(key, -1);
	if (keybio == NULL)
	{
		qDebug() << "Failed to create key BIO";
		return 0;
	}
	if (publi == KEY_PUBLIC)
	{
		rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);
	}
	else
	{
		rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);
	}
	if (rsa == NULL)
	{
		qDebug() << "Failed to create RSA";
	}
	return rsa;
}

QString SecurityVerification::rsaEncryption(QString &data, QString &keystr) //私钥加密
{
	unsigned char encrypted[1024] = { 0 };
	QByteArray keyData = keystr.toLocal8Bit();
	unsigned char *key = (unsigned char*)strdup(keyData.constData());
	RSA * rsa = rsaCreate(key, KEY_PRIVATE);
	if (rsa == NULL)
		return NULL;
	free(key);
	QByteArray encData = QByteArray::fromStdString(data.toStdString()).toBase64(QByteArray::Base64Encoding);
	int dataLen = encData.length();
	int  result = RSA_private_encrypt(dataLen, (unsigned char*)encData.data(), encrypted, rsa, RSA_PKCS1_PADDING);
	if (result < 0)
	{
		qDebug() << "Failed to create rsaEncryption";
		return NULL;
	}
	else
	{
		QByteArray signByteArray = QByteArray::fromRawData((const char *)encrypted, RSA_size(rsa));
		QString str(signByteArray.toHex());
		return str;
	}
}

QString SecurityVerification::rsaDecryption(QString &data, QString &keystr) //公钥解密
{
	unsigned char decrypted[1024] = { 0 };
	QByteArray keyData = keystr.toLocal8Bit();
	unsigned char *key = (unsigned char*)strdup(keyData.constData());
	RSA * rsa = rsaCreate(key, KEY_PUBLIC);
	if (rsa == NULL)
		return NULL;
	free(key);
	int rsasize = RSA_size(rsa);
	QByteArray encData = QByteArray::fromHex(QByteArray::fromStdString(data.toStdString()));
	int dataLen = encData.length();
	int  result = RSA_public_decrypt(dataLen, (unsigned char*)encData.data(), decrypted, rsa, RSA_PKCS1_PADDING);
	if (result < 0)
	{
		qDebug() << "Failed to rsaDecryption";
		return NULL;
	}
	else
	{
		QByteArray decdata((char*)decrypted);
		QByteArray b1 = QByteArray::fromBase64(decdata, QByteArray::Base64Encoding);
		std::string str = b1.toStdString();
		return QString::fromStdString(str);
	}
}

QString SecurityVerification::desEncryption(QString &data, QString &keystr) //加密
{
	unsigned char encrypted[1024] = { 0 };
	QByteArray keyData = keystr.toLocal8Bit();
	DES_key_schedule schedule;
	char *key = (char*)strdup(keyData.constData());
	DES_cblock keyEncrypt;
	DES_cblock ivec;
	//IV设置为0x0000000000000000  ，也可以设置其他值，但是加密和解密的IV要一样
	memset((char*)&ivec, 0, sizeof(ivec));

	memcpy(keyEncrypt, key, 8);
	DES_set_key_unchecked(&keyEncrypt, &schedule);
	free(key);
	QByteArray encData = QByteArray::fromStdString(data.toStdString()).toBase64(QByteArray::Base64Encoding);
	int dataLen = encData.length();
	DES_ncbc_encrypt((unsigned char*)encData.data(), encrypted, dataLen, &schedule, &ivec, DES_ENCRYPT);
	int outlen = (dataLen + 7) / 8 * 8;//密钥长度不够8位会自动补齐
	QByteArray signByteArray = QByteArray::fromRawData((const char *)encrypted, outlen);
	QString str(signByteArray.toHex());
	return str;
}

QString SecurityVerification::desDecryption(QString &data, QString &keystr) //解密
{
	unsigned char decrypted[1024] = { 0 };
	QByteArray keyData = keystr.toLocal8Bit();
	DES_key_schedule schedule;
	char *key = (char*)strdup(keyData.constData());
	DES_cblock keyEncrypt;
	DES_cblock ivec;
	//IV设置为0x0000000000000000 ，也可以设置其他值，但是加密和解密的IV要一样  
	memset((char*)&ivec, 0, sizeof(ivec));

	memcpy(keyEncrypt, key, 8);
	DES_set_key_unchecked(&keyEncrypt, &schedule);
	free(key);
	QByteArray encData = QByteArray::fromHex(QByteArray::fromStdString(data.toStdString()));
	int dataLen = encData.length();

	DES_ncbc_encrypt((unsigned char*)encData.data(), decrypted, dataLen, &schedule, &ivec, DES_DECRYPT);
	QByteArray decdata((char*)decrypted);
	QByteArray b1 = QByteArray::fromBase64(decdata, QByteArray::Base64Encoding);
	std::string str = b1.toStdString();
	return QString::fromStdString(str);
}