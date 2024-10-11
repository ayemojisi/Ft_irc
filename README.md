# 42 Irc Project (WIP)

<!--toc:start-->
- [42 Irc Project (WIP)](#42-irc-project-wip)
  - [Usage](#usage)
  - [Description](#description)
  - [Development](#development)
    - [Dependencies](#dependencies)
    - [Installation](#installation)
    - [Terms](#terms)
<!--toc:end-->

---

## Usage

---
bu komutu calistirarak serveri baslatabilirsiniz.

```bash
 ./ircserv <port> <password>
```

## Description

---
Bu projenin amaci irc protocollerine uygun server yazmaktir.
Server port ve password alarak calisir.
size sunucuyu yonetmezniz icin basit bir terminal arayuzu ile sizi yaniz birakir.

bu arayuzde kullanabileceginiz komutlar asagidaki gibidir.

```bash
# sunucu komutlari
 /quit #sunucuyu kapatir
 /restart #sunucuyu yeniden baslatir
 /backup #sunucuyu yedekler
 /backupload #sunucuyu yedekten geri yukler
# kanal komutlari
 /channellist #sunucuda bulunan kanallari listeler
 /channelinfo <channel_name> #kanal hakkinda bilgi verir
 /channelcreate <channel_name> #kanal olusturur
 /channeldelete <channel_name> #kanali siler
 /channeluserlist <channel_name> #kanalda bulunan kullanicilari listeler
 /channeljoin <channel_name> #kullaniciyi kanala ekler
 /channelleave <channel_name> #kullaniciyi kanaldan cikarir
 /channelkick <channel_name> <user_name> #kullaniciyi kanaldan atar
 /channelban <channel_name> <user_name> #kullaniciyi kanaldan banlar
 /channelunban <channel_name> <user_name> #kullaniciyi ban listesinden cikarir
 /channelmute <channel_name> <user_name> #kullaniciyi kanalda susturur
 /channelunmute <channel_name> <user_name> #kullaniciyi kanalda susturmayi kaldirir
 /channelop <channel_name> <user_name> #kullaniciyi kanalda op yapar
 /channeldeop <channel_name> <user_name> #kullaniciyi kanalda op yapmayi kaldirir
 /channeltopic <channel_name> <topic> #kanal konusunu degistirir
 /chaneelclear <channel_name> #kanal mesajlarini siler
 /channelmsg <channel_name> <message> #kanala mesaj gonderir
 /channelmsgall <message> #tum kanallara mesaj gonderir
 /channelmsgop <channel_name> <message> #kanalda op olan kullanicilara mesaj gonderir
 /channelmsgusers <channel_name> <message> #kanalda bulunan kullanicilara mesaj gonderir
 /channelmsgmute <channel_name> <message> #kanalda susturulan kullanicilara mesaj gonderir
 /channelbacklog <channel_name> #kanalda bulunan mesajlari listeler
 /channelbacklog <channel_name> <n> #kanalda bulunan son n mesajlari listeler
# kullanici komutlari
 /userlist #sunucuda bulunan kullanicilari listeler
 /userinfo <user_name> #kullanici hakkinda bilgi verir
 /userkick <user_name> #kullaniciyi sunucudan atar
 /userban <user_name> #kullaniciyi sunucudan banlar
 /userunban <user_name> #kullaniciyi ban listesinden cikarir
 /usermute <user_name> #kullaniciyi susturur
 /userunmute <user_name> #kullaniciyi susturmayi kaldirir
 /userop <user_name> #kullaniciyi op yapar
 /userdeop <user_name> #kullaniciyi op yapmayi kaldirir
# mesaj komutlari
 /msg <user_name> <message> #kullanicilara ozel mesaj gonderir
```

## Development

---

### Dependencies

---
Bu projede ki amacimiz socket kavramini ogrenmek ve bir irc serverin icinde ki verileri nasil yonetebilecegimizi ogrenmektir.

### Installation

---
Tek yapmaniz gereken projeyi reposunu cekip make komutunu calistirmaktir.
(sadece linux ve macos icin gecerlidir)

```bash
git clone https://gitlab.com/Pometcan/irc
cd irc
make
```

### Terms

---

| Term | Description
| --- | ---
| IRC | Internet Relay Chat
| Socket | Iki bilgisayar arasinda veri alisverisi yapmak icin kullanilan bir yazilimdir.
| bind | Bir socketi bir adres ve port numarasi ile baglamak icin kullanilan bir fonksiyondur.
| listen | Socketin dinlemeye baslamasi icin kullanilan bir fonksiyondur.
| accept | Socketten gelen baglantilari kabul etmek icin kullanilan bir fonksiyondur.
| close | Socketi kapatmak icin kullanilan bir fonksiyondur.
| send | Sockete veri gondermek icin kullanilan bir fonksiyondur.
| recv | Socketten veri almak icin kullanilan bir fonksiyondur.
| poll | Bir veya birden fazla socketin durumunu kontrol etmek icin kullanilan bir fonksiyondur.
| AF_INET | Internet Protocol version 4 (IPv4)
| SOCK_STREAM | TCP
| SOCK_DGRAM | UDP
| IPPROTO_TCP | TCP protokolünü kullanmak için.
| IPPROTO_UDP | UDP protokolünü kullanmak için.

| int fcntl(int fd, int cmd, ...) | ... 
| --- | ---
| cmd | fcntl'in ne tür bir işlem yapacağını belirleyen komuttur. Yaygın komutlar şunlardır:
| F_GETFL | Dosya durum bayraklarını alır.
| F_SETFL | Dosya durum bayraklarını ayarlar (örneğin O_NONBLOCK gibi).
| F_GETFD | Dosya tanıtıcısının bayraklarını alır.
| F_SETFD | Dosya tanıtıcısının bayraklarını ayarlar.
| F_SETLK, F_SETLKW, F_GETLK | Dosya kilitleme işlemleri.
| O_NONBLOCK | Okuma/Yazma modunda işlem yarım kaldıysa/tamamlanamıyorsa threadi bekletme özelliğini kaldırır beklemez program devam eder

| Struct | Description
| --- | ---
| serverAddress | Sunucunun adresini tutan bir structtur.
| clientAddress | Clientin adresini tutan bir structtur.
| serverSocket | Sunucunun socketini tutan bir degiskendir.
| clientSocket | Clientin socketini tutan bir degiskendir.
| sin_family | Adresin ailesini tutan bir degiskendir.
| sin_port | Port numarasini tutan bir degiskendir.
| sin_addr | IP adresini tutan bir degiskendir.