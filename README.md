# Student Grade Management System / Öğrenci Bilgi Sistemi

A terminal-based C++ application designed to manage student grades, calculate letter grades, and track attendance using dynamic File I/O operations. 

---

* 🇹🇷 Detaylı Proje Dokümantasyonu

### 1. Projenin Amacı ve Genel Yapısı
Bu proje, **C++** programlama dili kullanılarak geliştirilmiş terminal tabanlı bir sistemdir. Sistem dinamik ölçme değerlendirme seçenekleri, not giriş sistemi, yoklama takibi ve harf notu hesaplanması işlemlerini yapabilmektedir. Tüm veriler dinamik olarak `.txt` dosyalarına kayıt edilmektedir.

### 2. Veri Yapıları
* **`struct Ders`**: Dersin kodu, adı ve haftalık ders saatini tutar.
* **`struct Ogrenci`**: Öğrenci numarası, adı, soyadı, toplam devamsızlık saatini ve devam durumunu saklar.
* **`struct harfOgr`**: Harf notu hesaplandıktan sonra öğrenci numarası, isim ve harf notunu listelerken kullanılmaktadır.

### 3. Dosya Yönetim Mimarisi
* **`dersKodlari.txt`**: Sistemin açılması için gereklidir. Derslerin tanımlı olduğu ana dosyadır.
* **`ogrenciListesi.txt`**: Öğrencilerin ana listesini tutar.
* **`[dersKodu]Aktiflik.txt`**: Hangi ölçme değerlendirmelerin aktif olduğunu saklar.
* **`[dersKodu]Yuzdelik.txt`**: Ölçme değerlendirmelerin yüzdelik ağırlıklarını saklar.
* **`[dersKodu]-[Hafta]HaftaYoklama.txt`**: Hafta bazında öğrencilerin yoklamalarının verilerini saklar.
* **`[dersKodu]YoklamaKilit.txt`**: Yoklaması girilen haftaların kilitlenip kilitlenmediği bilgisini tutar.
* **`[dersKodu]DVDZ.txt`**: Öğrencilerin devamsızlıktan kalıp/geçtiği bilgisini saklar.
* **`[dersKodu]HarfNotu.txt`**: Hesaplanan harf notlarının ve puanların verisini saklar.

### 4. Temel Modüller ve Fonksiyonlar
**A. Ölçme ve Değerlendirme Fonksiyonu**
* **Dinamik seçim:** İstenen ölçme değerlendirmelerin aktif/pasif edilmesi.
* **Bağımlılık kontrol sistemi:** 2. ölçme değerlendirme seçeneklerini açmak için ilkinin de aktif edilmesi gerekmektedir.

**B. Yüzdelik Dilim Ayarlama Fonksiyonu**
* Aktif derslere yüzdeliklerin atanmasına yarar.
* **Doğrulama sistemi:** Sistemin toplam yüzdesinin 100'e eşit olduğunun kontrolü yapılır.

**C. Yoklama Fonksiyonu**
* **Hafta bazlı giriş sistemi:** Her haftanın yoklamasının teker teker girdilerinin alınması.
* **Kilit mekanizması:** Girilen haftanın yoklamaları kayıt edildikten sonra değiştirilemez.

**D. Devamsızlık Hesaplama Fonksiyonu**
* **Kontrol Sistemi:** Tüm haftaların yoklamalarının girişinin yapılması gerekmektedir.
* Devamsızlık sınırı otomatik hesaplanır ve ilgili dosyaya yazılır.

**E. Not Giriş Fonksiyonu**
* **Kontrol Sistemi:** Aktif olan dersler sıralanır ve sadece onların girişine izin verilir.
* Öğrenciler sıralanır ve not girişi yapılır. Notuna `-99` girilmesi halinde ise öğrencinin notu yoktur ya da sınava gelmemiş kabul edilir.
* **Final Kontrol Sistemi:** Final notu girişi için tüm yoklamaların girişinin yapılması gerekmektedir.

**F. Harf Notu Hesaplama Fonksiyonu**
* Tüm not dosyalarının okunması ardından ilgili yüzdelikler ile çarpılıp öğrencilerin harf notları hesaplanır ve ilgili dosyaya kayıt edilir.

### 5. Menü İşlevleri
*(Sistem; Ders İşlemleri, Yoklama, Not Girişi ve Ölçme Değerlendirme gibi katmanlı menü yapılarıyla, kullanıcı giriş (input) hatalarını engelleyecek kontrollerle tasarlanmıştır.)*
