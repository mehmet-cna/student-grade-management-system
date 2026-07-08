#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>

using namespace std;
// Dersin kodunu ve adini tutmak icin struct yapisi kullanimi
struct Ders {
  string kod;
  string ad;
  int saat;
};
// Ogrenci bilgilerini ve devamsızlığını tuttuğumuz struct yapısı
struct Ogrenci {
  int no;
  string ad;
  string soyad;
  int saat;
  string devamlilik;
};
// fonksiyonlarin tanimlanmasi
void anaMenu(Ders gelenDers);
void yoklamaMenu(Ders gelenDers);
void yoklamaIslem(int hafta, Ders gelenDers);
void olcmeDegerlendirmeSecMenu(Ders gelenDers);
void notGirisMenu(Ders gelenDers);
void notGiris(Ders gelenDers, string islemdekiDers);
void yuzdelikMenu(Ders gelenDers);
void devamHesaplama(Ders gelenDers);
void DersKoduHarfNotları(Ders gelenDers);
void harfNotuMenusu(Ders gelenDers);
// Programın ana giriş fonksiyonu
int main() {
  // Gerekli değişkenlerin tanımlanması
  unsigned int islem;
  int tempSaat;
  string tempKod, tempAd;
  string ayirac = "============================================================";
  // Dersler dosyasının okunması
  ifstream derslerOku("dersKodlari.txt");
  // Dosyanın kontrolü eğer yok ise program sonlanır
  if (!derslerOku.is_open()) {
    cerr << "'dersKodlari.txt' Dosyasi bulunamadi!" << endl;
    return 1;
  }
  vector < Ders > dersListe;
  // Derslerin okunması ve onlar ile ders nesnelerinin oluşturulması
  while (derslerOku >> tempKod >> tempAd >> tempSaat) {
    Ders yeniDers;
    yeniDers.kod = tempKod;
    yeniDers.ad = tempAd;
    yeniDers.saat = tempSaat;
    // Vektor içine kayıt işlemi
    dersListe.push_back(yeniDers);
  }
  derslerOku.close();
  // Ders seçim menüsünün döngüsü
  while (true) {
    cout << endl;
    // Vector içerisinde listelenen derslerin ekrana basılması
    for (unsigned int i = 0; i < dersListe.size(); i++) {
      cout << i + 1 << ". " << dersListe[i].kod << " - " << dersListe[i].ad << endl;
    }
    cout << endl << "Lutfen Yapmak Istediginiz Islemi Seciniz (1,2,3...)" << endl;
    cout << "Cikis Yapmak Icin '0' i tuslayiniz!" << endl;
    cin >> islem;
    if (cin.fail()) {
      cout << "\n=================================" << endl;
      cout << "Lütfen Yapcağınız İşlemin Başndaki Değeri Giriniz!" << endl;
      cout << "=================================" << endl;
      cin.clear();
      cin.ignore(numeric_limits < streamsize > ::max(), '\n');
      continue;
    }
    cout << endl;
    // Seçim Kontrolğ
    if (islem == 0) {
      cout << "Sistemden cikis yapiliyor..." << endl;
      break;
    }
    //Seçilen derse göre işlem menüsüne yönelendirilmesi
    if (islem > 0 && islem <= dersListe.size()) {
      anaMenu(dersListe[islem - 1]);
    }
  }
}
// Ders işlem menüsü fonksiyonu
void anaMenu(Ders gelenDers) {
  //İlgili değişkenlerin tanımlanması
  Ders gidenDers = gelenDers;
  int secim;
  string ayirac = "============================================================";
  // Seçilen Derse Göre Dinamik Dosya İsimlerinin Belirlenmesi
  string olcmeDosya = gelenDers.kod + "Aktiflik.txt";
  string yuzdeDosya = gelenDers.kod + "Yuzdelik.txt";
  // Menü döngüsü
  while (true) {
    //Menü döngüsünün ekrana basılması
    cout << endl << ayirac << endl;
    cout << "Secili Ders: " << gelenDers.kod << " - " << gelenDers.ad << endl << endl;
    cout << "1) Olcme Degerlendirme Secim Menusu" << endl;
    cout << "2) Yuzdelik Ayarlama Menusu" << endl;
    cout << "3) Not Giris Menusu" << endl;
    cout << "4) Yoklama Menusu" << endl;
    cout << "5) Harf Notu Goruntuleme Menusu" << endl;
    cout << endl << "Ders Secim Menusune Donmek Icin '0'i Tuslayiniz" << endl;
    cout << "Lutfen Yapmak Istediginiz Islemin Numarasını Seciniz(1,2,3,...)" << endl;
    cin >> secim;
    if (cin.fail()) {
      cout << "\n=================================" << endl;
      cout << "Lütfen Yapcağınız İşlemin Başndaki Değeri Giriniz!" << endl;
      cout << "=================================" << endl;
      cin.clear();
      cin.ignore(numeric_limits < streamsize > ::max(), '\n');
      continue;
    }
    // Secilen işleme göre ilgili fonksiyona yönlendirilmesi
    if (secim == 0) {
      return;
    } else if (secim == 1) {
      // Eğer ölçme değerlendirme önceden belirlendi ise değiştirilemeyeceğine dair uyarı vermesi
      ifstream olcmeKilit(olcmeDosya);
      if (olcmeKilit.is_open()) {
        cout << endl << ayirac << endl << "Dersin Olcme DegerlendirmeleriBelirlenmistir!" << endl;
        cout << "Olcme Degerlendirmeler Degistirilemez!" << endl << ayirac << endl;
        olcmeKilit.close();
      } else {
        olcmeDegerlendirmeSecMenu(gidenDers);
      }
    } else if (secim == 2) {
      //Eğer yüzdelik belirlendi ise değiştirilemeyeceğine dair uyarı yazdırılması
      ifstream yuzdeKilit(yuzdeDosya);
      if (yuzdeKilit.is_open()) {
        cout << endl << ayirac << endl << "Dersin Yuzdelikleri Belirlenmistir!" <<
          endl;
        cout << "Yuzdelikler Degistirilemez!" << endl << ayirac << endl;
        yuzdeKilit.close();
      } else {
        yuzdelikMenu(gidenDers);
      }
    } else if (secim == 3) {
      notGirisMenu(gidenDers);
    } else if (secim == 4) {
      yoklamaMenu(gidenDers);
    } else if (secim == 5) {
      harfNotuMenusu(gidenDers);
    } else {
      cout << endl << ayirac << endl << "Gecersiz Deger Girdiniz!" << endl;
      cout << "Lutfen Farkli Bir Deger Giriniz!" << endl << ayirac << endl;
    }
  }
}
void yoklamaMenu(Ders gelenDers) {
  // İlgili değişkenlerin tanımlanması
  Ders gidenDers = gelenDers;
  string ayirac = "============================================================";
  // Menü döngüsü
  while (true) {
    int hafta;
    devamHesaplama(gelenDers);
    // Menünün ekrana basılması
    cout << endl << ayirac << endl;
    cout << "Secilen Ders:" << gelenDers.kod << " - " << gelenDers.ad << endl;
    cout << endl << "1) 1.Hafta Yoklama Girisi" << endl;
    cout << "2) 2.Hafta Yoklama Girisi" << endl;
    cout << "3) 3.Hafta Yoklama Girisi" << endl;
    cout << "4) 4.Hafta Yoklama Girisi" << endl;
    cout << "5) 5.Hafta Yoklama Girisi" << endl;
    cout << "6) 6.Hafta Yoklama Girisi" << endl;
    cout << "7) 7.Hafta Yoklama Girisi" << endl;
    cout << "8) 8.Hafta Yoklama Girisi" << endl;
    cout << "9) 9.Hafta Yoklama Girisi" << endl;
    cout << "10) 10.Hafta Yoklama Girisi" << endl;
    cout << "11) 11.Hafta Yoklama G irisi" << endl;
    cout << "12) 12.Hafta Yoklama Girisi" << endl;
    cout << "13) 13.Hafta Yoklama Girisi" << endl;
    cout << "14) 14.Hafta Yoklama Girisi" << endl;
    cout << endl << "Cikis Yapmak Icin '0' i Tuslayiniz" << endl;
    cout << "Lutfen Yoklamasini Girmek Istediginiz Haftayi Seciniz: " << endl;
    cin >> hafta;
    if (cin.fail()) {
      cout << "\n=================================" << endl;
      cout << "Lütfen Yapcağınız İşlemin Başndaki Değeri Giriniz!" << endl;
      cout << "=================================" << endl;
      cin.clear();
      cin.ignore(numeric_limits < streamsize > ::max(), '\n');
      continue;
    }
    // Seçilen haftaya göre haftanın yoklama fonksiyonuna yönlendirilmesi
    if (hafta == 0) {
      return;
    } else if (hafta > 0 && hafta <= 14) {
      yoklamaIslem(hafta, gidenDers);
    } else {
      cout << endl << ayirac << endl << "Gecersiz Hafta Girdiniz Lutfen Gecerli DegerGiriniz!" << endl << ayirac << endl;
    }
  }
}
// Yoklama girdisinin alınması ve kaydedilmesi fonksiyonu
void yoklamaIslem(int hafta, Ders gelenDers) {
  // İlgili değişkenlerin tanımlanması
  string ayirac = "============================================================";
  string kilitDosya = gelenDers.kod + "YoklamaKilit.txt";
  int haftalar[14] = {
    0
  };
  // Yoklama kilit dosyasının kontrol edilmesi
  // Eger yok ise oluşturulması
  ifstream kontrolOku(kilitDosya);
  if (!kontrolOku.is_open()) {
    ofstream olustur(kilitDosya);
    olustur << "0 0 0 0 0 0 0 0 0 0 0 0 0 0"; // Standart olarak tüm yoklamalar açık olmalı
    olustur.close();
  } else {
    for (int i = 0; i < 14; i++) {
      if (!(kontrolOku >> haftalar[i])) haftalar[i] = 0;
    }
    kontrolOku.close();
  }
  // Seçilen hafta kilitli ise o haftanın kilit olduğuna dair uyarı verilmesi
  if (haftalar[hafta - 1] == 1) {
    cout << endl << ayirac << endl << "BU HAFTANIN GIRISI YAPILMISTIR VE DEGISTIRILEMEZ!" <<
      endl << ayirac << endl;
    return;
  }
  // Öğrenci listesinin okunması bulunanaması durumunda sistemin hata vermesi ve üst menüye dönmesi
  ifstream ogrenciListesiOku("ogrenciListesi.txt");
  if (!ogrenciListesiOku.is_open()) {
    cerr << "ogrenciListesi.txt bulunamadi!" << endl;
    return;
  }
  // Hafta ve Ders koduna göre dinamik yoklama dosyasının oluşturulması
  string dosyaAdi = gelenDers.kod + "-" + to_string(hafta) + "HaftaYoklama.txt";
  ofstream yoklamaDosya(dosyaAdi);
  int ogrenciNo;
  string ogrenciAd, ogrenciSoyad;
  // Ana yoklama girme döngüsü
  while (ogrenciListesiOku >> ogrenciNo >> ogrenciAd >> ogrenciSoyad) {
    int islemSaat;
    // Öğrencilerin sıra ile listelenmesi ve yoklama girdilerinin alınması
    hatali:
      cout << endl << ayirac << endl;
    cout << "Ogrenci: " << ogrenciNo << " - " << ogrenciAd << " " << ogrenciSoyad << endl;
    cout << "Gelmedigi Saat (Max " << gelenDers.saat << "): ";
    cin >> islemSaat;
    if (cin.fail()) {
      cout << "\n=================================" << endl;
      cout << "Lütfen Yapcağınız İşlemin Başndaki Değeri Giriniz!" << endl;
      cout << "=================================" << endl;
      cin.clear();
      cin.ignore(numeric_limits < streamsize > ::max(), '\n');
      continue;
    }
    // Girilen saat değerinin dersin haftalık saati ile kontrol edilmesi
    if (islemSaat <= gelenDers.saat && islemSaat >= 0) {
      yoklamaDosya << ogrenciNo << " " << ogrenciAd << " " << ogrenciSoyad << " " << islemSaat << endl;
    } else {
      cout << "HATA: Gecersiz saat girdiniz!" << endl;
      goto hatali; // Eğer girilen değer hatalı ise uyarı verilmesi ve tekrardan öğrencinin yoklamasının istenmesi
    }
  }
  yoklamaDosya.close();
  ogrenciListesiOku.close();
  // Girilen yoklama listesinin onaylanması
  char onay;
  cout << endl << "Yoklama girisini onayliyor musunuz? (e/h): ";
  cin >> onay;
  // Eğer onaylıyor ise kaydedilmesi
  if (onay == 'e' || onay == 'E') {
    haftalar[hafta - 1] = 1;

    ofstream kilitYaz(kilitDosya);
    for (int i = 0; i < 14; i++) {
      kilitYaz << haftalar[i] << (i == 13 ? "" : " ");
    }
    kilitYaz.close();
    cout << "Islem tamamlandi ve hafta kilitlendi." << endl;
  } else {
    cout << "Islem iptal edildi, dosya kilitlenmedi." << endl;
  }
  devamHesaplama(gelenDers);
}
// Ölçme Değerlendirme karar verme fonksiyonu
void olcmeDegerlendirmeSecMenu(Ders gelenDers) {
  // İlgili deişkenlerin tanımlanması
  string ayirac =
    "============================================================";
  // Ders koduna göre dinamik ders aktiflik dosyasının tanımlanması
  string AktiflikDosya = gelenDers.kod + "Aktiflik.txt";
  cout << endl << ayirac << endl;
  cout << gelenDers.kod << "-" << gelenDers.ad << endl;
  cout << "Vize1 ve Final bilgileri zorunludur ve Aktiflik Değiştirilemez." << endl << endl;
  int islem;
  int Vize1 = 1, Vize2 = 0, Final = 1, KisaSinav1 = 0, KisaSinav2 = 0, Odev1 = 0, Odev2 = 0, Proje1 = 0, Proje2 = 0;
  string HATA1 = "============================================================\nBirincil Ölçme GirilmedenBu Seçenek Kullanılamaz \n============================================================";
  string HATA2 = "============================================================\nİkincil Ölçme KaldırılmadanBu Seçenek Kullanılamaz \n============================================================";
  string onay;
  // Menü döngüsü
  while (true) {
    // Menünün ekrana basılması
    cout << "1) Vize 2 = " << Vize2 << endl;
    cout << "2) KısaSınav 1 = " << KisaSinav1 << endl;
    cout << "3) KısaSınav 2 = " << KisaSinav2 << endl;
    cout << "4) Odev 1 = " << Odev1 << endl;
    cout << "5) Odev 2 = " << Odev2 << endl;
    cout << "6) Proje 1 = " << Proje1 << endl;
    cout << "7) Proje 2 = " << Proje2 << endl << endl;

    cout << "Değerlendirme Eşliği 1 İse Aktif, 0 İse Pasif Durumdadır" << endl;
    cout << "Değiştirmek istediğiniz değeri seçiniz." << endl << endl;
    cout << "Kaydetmek için “99” tuşlayınız." << endl;
    cout << "Onaylamadan Çıkış Ypamak İçin 0'ı Seçiniz" << endl;
    cin >> islem;
    if (cin.fail()) {
      cout << "\n=================================" << endl;
      cout << "Lütfen Yapcağınız İşlemin Başndaki Değeri Giriniz!" << endl;
      cout << "=================================" << endl;
      cin.clear();
      cin.ignore(numeric_limits < streamsize > ::max(), '\n');
      continue;
    }
    // Secilen işleme göre aktif pasif edilmesi
    // Secilen değişkenin bağlı olduğu değişkenlerin kontrolü
    if (islem == 1 && Vize2 == 0) {
      Vize2 = 1;
    } else if (islem == 1 && Vize2 == 1) {
      Vize2 = 0;
    }
    if (islem == 2 && KisaSinav1 == 0) {
      KisaSinav1 = 1;
    } else if (islem == 2 && KisaSinav1 == 1 && KisaSinav2 == 0) {
      KisaSinav1 = 0;
    } else if (islem == 2 && KisaSinav1 == 1 && KisaSinav2 == 1) {
      cout << HATA2 << endl;
    }
    if (islem == 3 && KisaSinav1 == 1 && KisaSinav2 == 0) {
      KisaSinav2 = 1;
    } else if (islem == 3 && KisaSinav1 == 1 && KisaSinav2 == 1) {
      KisaSinav2 = 0;
    } else if (islem == 3 && KisaSinav1 == 0) {
      cout << HATA1 << endl;
    }
    if (islem == 4 && Odev1 == 0) {
      Odev1 = 1;
    } else if (islem == 4 && Odev1 == 1 && Odev2 == 0) {
      Odev1 = 0;
    } else if (islem == 4 && Odev1 == 1 && Odev2 == 1) {
      cout << HATA2 << endl;
    }
    if (islem == 5 && Odev1 == 1 && Odev2 == 0) {
      Odev2 = 1;
    } else if (islem == 5 && Odev1 == 1 && Odev2 == 1) {
      Odev2 = 0;
    } else if (islem == 5 && Odev1 == 0) {
      cout << HATA1 << endl;
    }
    if (islem == 6 && Proje1 == 0) {
      Proje1 = 1;
    } else if (islem == 6 && Proje1 == 1 && Proje2 == 0) {
      Proje1 = 0;
    } else if (islem == 6 && Proje1 == 1 && Proje2 == 1) {
      cout << HATA2 << endl;
    }
    if (islem == 7 && Proje1 == 1 && Proje2 == 0) {
      Proje2 = 1;
    } else if (islem == 7 && Proje1 == 1 && Proje2 == 1) {
      Proje2 = 0;
    } else if (islem == 7 && Proje1 == 0) {
      cout << HATA1 << endl;
    }
    // Onaylama ve kaydetme islemi
    if (islem == 99) {
      cout << "Onaylıyor Musunuz? (e/h)" << endl;
      cin >> onay;
      if (onay == "e") {
        ofstream aktiflikOku(AktiflikDosya);
        if (aktiflikOku.is_open()) {
          aktiflikOku << Vize1 << " " << Final << " " << Vize2 << " " <<
            KisaSinav1 << " " << KisaSinav2 << " " << Odev1 << " " << Odev2 << " " << Proje1 << " " << Proje2 << endl;
          return;
        }
      }
      if (onay == "h") {}
    }
    if (islem == 0) {
      return;
    }
  }
}
// Not girişi menüsü fonksiyonu
void notGirisMenu(Ders gelenDers) {
  // İlgili değişkenlerin tanımlanması
  int araS1, donemSS, araS2, kisaS1, kisaS2, odev1, odev2, proje1, proje2;
  string ayirac = "============================================================";
  string secim;
  // Dinamik aktiflik dosyasının tanımlanması
  string aktiflikDosya = gelenDers.kod + "Aktiflik.txt";
  ifstream aktiflikDosyaOku(aktiflikDosya);
  // Aktiflik dosyasını bulanamaz ise hata verip üstmenüye dönmesi
  if (!aktiflikDosyaOku.is_open()) {
    cerr << endl << ayirac << endl << "'" << aktiflikDosya << "' Dosyasi Bulunamadi!" << endl <<
      ayirac << endl;
    return;
  }
  // Aktif olan derslerin okunması ve ilgili değişkenlere tanımlanması
  while (aktiflikDosyaOku >> araS1 >> donemSS >> araS2 >> kisaS1 >> kisaS2 >> odev1 >> odev2 >>
    proje1 >> proje2) {}
  // Aktif dersler menüsü döngüsü
  while (true) {
    cout << endl << ayirac << endl << "Secili Ders: " << gelenDers.kod << " - " << gelenDers.ad <<
      endl << endl;
    // Aktif derslerin kontrolü ve ekrana basılması
    if (araS1 == 1) {
      cout << "Ara Sinav 1 (ara1)" << endl;
    }
    if (donemSS == 1) {
      cout << "Donem Sonu Sinavi (final)" << endl;
    }
    if (araS2 == 1) {
      cout << "Ara Sinav 2 (ara2)" << endl;
    }
    if (kisaS1 == 1) {
      cout << "Kisa Sinav 1 (kisa1)" << endl;
    }
    if (kisaS2 == 1) {
      cout << "Kisa Sinav 2 (kisa2)" << endl;
    }
    if (odev1 == 1) {
      cout << "Odev 1 (odev1)" << endl;
    }
    if (odev2 == 1) {
      cout << "Odev 2 (odev2)" << endl;
    }
    if (proje1 == 1) {
      cout << "Proje 1 (proje1)" << endl;
    }
    if (proje2 == 1) {
      cout << "Proje 2 (proje2)" << endl;
    }
    cout << endl << "Cikis Yapmak Icin 'cikis' yaziniz" << endl;
    cout << "Lutfen Yapmak Istediginiz Islemin Ismini Giriniz: " << endl;
    cin >> secim;
    // Secilen isleme göre gerekli fonksiyonların çalıştırılması
    if (secim == "cikis" || secim == "CIKIS" || secim == "Cikis" || secim == "exit") {
      return;
    } else if (secim == "ara1" && araS1 == 1) {
      notGiris(gelenDers, secim);
    }
    // Eğer seçim final ise yoklamadan kalanların listesinin kontrolü
    else if (secim == "final" && donemSS == 1) {
      string dzdzDosya = gelenDers.kod + "DVDZ.txt";
      ifstream dvdzOku(dzdzDosya);
      if (dvdzOku.is_open()) {
        notGiris(gelenDers, secim);
      } else {
        cerr << endl << ayirac << endl << "Final Notu Girisi Yapmak Icin YoklamalariTamamlamaniz Gerekmektedir!" << endl << ayirac << endl;
      }
    }
    // Seçimin aktif ise ilgili fonksiyonun çalıştırılması
    else if (secim == "ara2" && araS2 == 1) {
      notGiris(gelenDers, secim);
    } else if (secim == "kisa1" && kisaS1 == 1) {
      notGiris(gelenDers, secim);
    } else if (secim == "kisa2" && kisaS2 == 1) {
      notGiris(gelenDers, secim);
    } else if (secim == "odev1" && odev1 == 1) {
      notGiris(gelenDers, secim);
    } else if (secim == "odev2" && odev2 == 1) {
      notGiris(gelenDers, secim);
    } else if (secim == "proje1" && proje1 == 1) {
      notGiris(gelenDers, secim);
    } else if (secim == "proje2" && proje2 == 1) {
      notGiris(gelenDers, secim);
    } else {
      cout << endl << ayirac << endl << "Gecersiz Deger Girdiniz Veya Girdiginiz Ders AktifDegil!" << endl << ayirac << endl;
    }
  }
}
// Not giriş fonksiyonu
void notGiris(Ders gelenDers, string islemdekiDers) {
  // İlgili değişkenlerin tanımlanması
  string ayirac = "============================================================";
  string isDers = islemdekiDers;
  int ogrenciNo;
  string ogrenciAd, ogrenciSoyad;
  int ogrenciNot;
  char onay;
  // Ders koduna ve secili ölçme değerlendirmeye göre dinamik dosya isimlerinin oluşturulması
  string ogrenciDosya = "ogrenciListesi.txt";
  string notDosya = gelenDers.kod + "-" + isDers + "Not.txt";
  ifstream kilitKontrol(notDosya);
  // Eğer notlar önceden girilmiş ise ekrana uyarı basılması ve değiştirilememesi
  if (kilitKontrol.is_open()) {
    cout << endl << ayirac << endl;
    cout << "UYARI: " << isDers << " Icin Not Girisi Daha Once Yapilmis!" << endl << ayirac <<
      endl;
    kilitKontrol.close();
    return;
  }
  ifstream ogrenciDosyaOku(ogrenciDosya);
  // Öğrenci listesinin kontrolü
  if (!ogrenciDosyaOku.is_open()) {
    cerr << endl << ayirac << endl << "'ogrenciListesi.txt' Dosyasi Bulunamadi!" << endl << ayirac <<
      endl;
    return;
  }
  cout << endl << ayirac << endl << "Secili Ders: " << gelenDers.kod << " - " << gelenDers.ad << endl;
  cout << "Secili Olcme Degerlendirme: " << isDers << endl;
  ofstream notDosyaYaz(notDosya);
  // Eğer seçili ölçme değerlendirme final ise
  if (isDers == "final") {
    // İlgili değişkenlerin tanımlanması
    int ogrenciDevamlilik;
    // Ders koduna göre dinamik dosya isimlerinin tanımlanması
    string devamliDosya = gelenDers.kod + "DVDZ.txt";
    string finalDosya = gelenDers.kod + "-finalNot.txt";
    ifstream devamlilikOku(devamliDosya);
    ofstream finalYaz(finalDosya);
    // Devamsızlık dosyasının okunması ve ilgili değişkenlere atanması
    while (devamlilikOku >> ogrenciNo >> ogrenciAd >> ogrenciSoyad >> ogrenciDevamlilik) {
      baslangic123:
        // Eğer öğrenci devamli ise not girişinin alınması
        if (ogrenciDevamlilik == 1) {
          cout << endl << ayirac << endl << ogrenciNo << " - " << ogrenciAd << " " <<
            ogrenciSoyad << endl;
          cout << "Ogrenci Sinava Gelmediyse '-99' Giriniz" << endl;
          cout << "Ogrencinin Aldigi Notu Giriniz: " << endl;
          cin >> ogrenciNot;
          if (cin.fail()) {
            cout << "\n=================================" << endl;
            cout << "Lütfen Yapcağınız İşlemin Başndaki Değeri Giriniz!" <<
              endl;
            cout << "=================================" << endl;
            cin.clear();
            cin.ignore(numeric_limits < streamsize > ::max(), '\n');
            continue;
          }
          // Girilen notun 0-100 aralığında olduğunun kontrol edilmesi
          if (ogrenciNot >= 0 && ogrenciNot <= 100) {
            cout << endl << "Notu Onayliyor Musunuz? (e/h): " << endl;
            cin >> onay;
            // Her not girişinden sonra onay alınması
            if (onay == 'e') {
              notDosyaYaz << ogrenciNo << " " << ogrenciAd << " " <<
                ogrenciSoyad << " " << ogrenciNot << endl;
            } else if (onay == 'h') {
              goto baslangic123;
            } else {
              cout << endl << ayirac << endl << "Hatali Deger Girdiniz!" <<
                endl << ayirac << endl;
              goto baslangic123;
            }
          }
          // Eğer -99 girdisi alındı ise not yerine -99 yazılması
          else if (ogrenciNot == -99) {
            notDosyaYaz << ogrenciNo << " " << ogrenciAd << " " <<
              ogrenciSoyad << " " << ogrenciNot << endl;
          } else {
            cout << endl << ayirac << endl << "Lutfen 0-100 Araliginda Yada -99Giriniz" << endl << ayirac << endl << endl;
            goto baslangic;
          }
        }
    }
    devamlilikOku.close();
    finalYaz.close();
  }
  // Seçilen ölçme değerlendirme final değil ise
  else {
    // Öğrenci listesinin okunması ve ilgili değişkenlere tanımlanması
    while (ogrenciDosyaOku >> ogrenciNo >> ogrenciAd >> ogrenciSoyad) {
      baslangic: cout << endl << ayirac << endl << ogrenciNo << " - " << ogrenciAd << " " <<
        ogrenciSoyad << endl;
      cout << "Ogrenci Sinava Gelmediyse '-99' Giriniz" << endl;
      cout << "Ogrencinin Aldigi Notu Giriniz : " << endl;
      cin >> ogrenciNot;
      if (cin.fail()) {
        cout << "\n=================================" << endl;
        cout << "Lütfen Yapcağınız İşlemin Başndaki Değeri Giriniz!" << endl;
        cout << "=================================" << endl;
        cin.clear();
        cin.ignore(numeric_limits < streamsize > ::max(), '\n');
        continue;
      }
      // Girilen notun 0-100 aralığında olduğunun kontrol edilmesi
      if (ogrenciNot >= 0 && ogrenciNot <= 100) {
        cout << endl << "Notu Onayliyor Musunuz? (e/h): " << endl;
        cin >> onay;
        // Her not girişinden sonra onay istenmesi
        if (onay == 'e') {
          notDosyaYaz << ogrenciNo << " " << ogrenciAd << " " <<
            ogrenciSoyad << " " << ogrenciNot << endl;
        } else if (onay == 'h') {
          goto baslangic;
        } else {
          cout << endl << ayirac << endl << "Hatali Deger Girdiniz!" << endl <<
            ayirac << endl;
          goto baslangic;
        }
      }
      // Eğer girilen not -99 ise not kısmına -99 yazdırılması
      else if (ogrenciNot == -99) {
        cout << endl << "Ogrenci Sinava Girmemistir Yada Notu Yoktur!" << endl;
        cout << "Onayliyor Musunuz? (e/h): " << endl;
        cin >> onay;
        //Not girişindne sonra onay istenmesi
        if (onay == 'e') {
          notDosyaYaz << ogrenciNo << " " << ogrenciAd << " " <<
            ogrenciSoyad << " " << ogrenciNot << endl;
        } else if (onay == 'h') {
          goto baslangic;
        } else {
          cout << endl << ayirac << endl << "Hatali Deger Girdiniz!" << endl <<
            ayirac << endl;
        }
      } else {
        cout << endl << ayirac << endl << "Lutfen 0-100 Araliginda Yada -99 Giriniz" <<
          endl << ayirac << endl << endl;
        goto baslangic;
      }
    }
  }
  ogrenciDosyaOku.close();
  notDosyaYaz.close();
}
// Yuzdelik menüsü fonksiyonu
void yuzdelikMenu(Ders gelenDers) {
  // İlgili değişkenlerin tanımlanası
  string ayirac = "============================================================";
  int araS1, araS2, donemSS, kisaS1, kisaS2, odev1, odev2, proje1, proje2;
  int araS1Y = 0, araS2Y = 0, donemSSY = 0, kisaS1Y = 0, kisaS2Y = 0, odev1Y = 0, odev2Y = 0, proje1Y =
    0, proje2Y = 0;
  string secim;
  string yuzdelikdosya = gelenDers.kod + "Yuzdelik.txt";
  int yuzde;
  string aktiflikDosya = gelenDers.kod + "Aktiflik.txt";
  // Dersin ölçme değerlendirmelerinin seçilip seçilmediğinin kontrol edilmesi
  ifstream aktiflikoku(aktiflikDosya);
  if (!aktiflikoku.is_open()) {
    // Eğer seçilmediyse önce o işlemin yapılması gerektiğinin uyarısı
    cerr << endl << ayirac << endl << "dersKoduAktiflik.txt Dosyasi bulunmadi!" << endl;
    cerr << "Lutfen Once Olcme Degerlendirme Menusunden, Olcme DegerlendirmeleriBelirleyiniz!" << endl << ayirac << endl;
    return;
  }
  // Menü döngüsü
  while (true) {
    baslangic: cout << endl << ayirac << endl << "Secili Ders: " << gelenDers.kod << " - " << gelenDers.ad <<
      endl;
    // AKtif olan derslerin okunması ve o derslerin ekrana yüzdelikleri ile birlikte basılması
    while (aktiflikoku >> araS1 >> donemSS >> araS2 >> kisaS1 >> kisaS2 >> odev1 >> odev2 >>
      proje1 >> proje2) {}
    if (araS1 == 1) {
      cout << "Ara Sinav 1 (ara1) = " << araS1Y << endl;
    }
    if (donemSS == 1) {
      cout << "Donem Sonu Sinavi 1 (final) = " << donemSSY << endl;
    }
    if (araS2 == 1) {
      cout << "Ara Sinav 2 (ara2) = " << araS2Y << endl;
    }
    if (kisaS1 == 1) {
      cout << "Kisa Sinav 1 (kisa1) = " << kisaS1Y << endl;
    }
    if (kisaS2 == 1) {
      cout << "Kisa Sinav 2 (kisa2) = " << kisaS2Y << endl;
    }
    if (odev1 == 1) {
      cout << "Odev 1 (odev1) = " << odev1Y << endl;
    }
    if (odev2 == 1) {
      cout << "Odev 2 (odev2) = " << odev2Y << endl;
    }
    if (proje1 == 1) {
      cout << "Proje 1 (proje1) = " << proje1Y << endl;
    }
    if (proje2 == 1) {
      cout << "Proje 2 (proje2) = " << proje2Y << endl;
    }
    cout << endl << "Cikis Yapmak Icin 0 i tuslayiniz" << endl;
    cout << "Yuzdeliklerin Girsini Yapip Kaydetmek Icin 'onay' yaziniz!" << endl;
    cout << "Lutfen Yuzdeligini Ayarlicaginiz Olcme Degerlendirmeyi Secin" << endl;
    cin >> secim;
    if (secim == "onay") {
      goto onayAdim;
    }
    if (secim == "0") {
      return;
    }
    // Seçilen ders kontrolü
    if (secim == "ara1" || secim == "final" || secim == "ara2" || secim == "kisa1" || secim == "kisa2" ||
      secim == "odev1" || secim == "odev2" || secim == "proje1" || secim == "proje2") {
      // Seçilen dersin yüzdeliğinin alınması
      cout << endl << "Yuzdelik yaziniz" << endl;
      cin >> yuzde;
      if (cin.fail()) {
        cout << "\n=================================" << endl;
        cout << "Lütfen Yapcağınız İşlemin Başndaki Değeri Giriniz!" << endl;
        cout << "=================================" << endl;
        cin.clear();
        cin.ignore(numeric_limits < streamsize > ::max(), '\n');
        continue;
      }
      if (yuzde > 0 && yuzde < 100) {
        if (secim == "ara1" && araS1 == 1) {
          araS1Y = yuzde;
        } else if (secim == "final" && donemSS == 1) {
          donemSSY = yuzde;
        } else if (secim == "ara2" && araS2 == 1) {
          araS2Y = yuzde;
        } else if (secim == "kisa1" && kisaS1 == 1) {
          kisaS1Y = yuzde;
        } else if (secim == "kisa2" && kisaS2 == 1) {
          kisaS2Y = yuzde;
        } else if (secim == "odev1" && odev1 == 1) {
          odev1Y = yuzde;
        } else if (secim == "odev2" && odev2 == 1) {
          odev2Y = yuzde;
        } else if (secim == "proje1" && proje1 == 1) {
          proje1Y = yuzde;
        } else if (secim == "proje2" && proje2 == 1) {
          proje2Y = yuzde;
        } else {
          cout << endl << ayirac << endl << "Secilen ders aktif degildir." << endl <<
            ayirac << endl;
        }
      } else if (yuzde == 0) {
        cout << endl << ayirac << endl << "Yuzdelik Deger 0 Olarak Girilemez!" <<
          endl << ayirac << endl;
      } else {
        cout << endl << ayirac << endl << "Girilen deger 0-100 aralığında olmalıdır." <<
          endl << ayirac << endl;
      }
    } else {
      cout << endl << ayirac << endl << "Gecerli bir deger giriniz." << endl << ayirac <<
        endl;
    }
  }
  onayAdim:
    // onay adımı
    // Girilen tüm yüzdeliklerin toplanması
    int toplamYuzde = araS1Y + donemSSY + araS2Y + kisaS1Y + kisaS2Y + odev1Y + odev2Y + proje1Y +
    proje2Y;
  // Girilen yüzdelikler toplamı 100 değil ise uyarı verilmesi
  if (toplamYuzde != 100) {
    cout << endl << ayirac << endl << "Tum Yuzdeler Toplami 100 olmak zorundadir." << endl <<
      ayirac << endl;
    goto baslangic;
  }
  // Eğer yüzdelikler toplamı 100 ise ilgili dosyaya yazdırılması
  if (toplamYuzde == 100) {
    ofstream yuzdelikOku(yuzdelikdosya);
    yuzdelikOku << araS1Y << " " << donemSSY << " " << araS2Y << " " << kisaS1Y << " " <<
      kisaS2Y << " " << odev1Y << " " << odev2Y << " " << proje1Y << " " << proje2Y << endl;
    return;
  }
}
// Ders devamsızlığı hesaplama fonksiyonu
void devamHesaplama(Ders gelenDers) {

  // İlgili değişkenlerin tanımlanması
  int totalSaat;
  double sinirSaat;
  int tempNo, tempSaat;
  string tempAd, tempSoyad;

  string dvdzDosya = gelenDers.kod + "DVDZ.txt";
  // Tüm haftaların yoklamalarının kontrol edilmesi
  for (int i = 1; i <= 14; i++) {
    string kontrolIsim = gelenDers.kod + "-" + to_string(i) + "HaftaYoklama.txt";
    ifstream kontrol(kontrolIsim);
    if (!kontrol.is_open()) {
      return;
    }
    kontrol.close();
  }

  vector < Ogrenci > ogrenciListe;

  string ilkHaftaDosya = gelenDers.kod + "-1HaftaYoklama.txt";
  ifstream ilkOku(ilkHaftaDosya);

  // İlk haftanın yoklamasının okunması
  while (ilkOku >> tempNo >> tempAd >> tempSoyad >> tempSaat) {

    // Öğrenci yapısının oluşturulması ve öğrencilerin kayıt edilmesi
    Ogrenci yeniOgr;
    yeniOgr.no = tempNo;
    yeniOgr.ad = tempAd;
    yeniOgr.soyad = tempSoyad;
    yeniOgr.saat = tempSaat;
    // Oluşturulan nesnenin vectore kayıt edilmesi
    ogrenciListe.push_back(yeniOgr);
  }
  ilkOku.close();
  // Kalan haftaların yoklama dosyalarının okunması ve ilgi nesnelere atanması
  for (int hafta = 2; hafta <= 14; hafta++) {

    string dosyaAdi = gelenDers.kod + "-" + to_string(hafta) + "HaftaYoklama.txt";
    ifstream dosyaOku(dosyaAdi);

    while (dosyaOku >> tempNo >> tempAd >> tempSoyad >> tempSaat) {

      for (size_t i = 0; i < ogrenciListe.size(); i++) {
        if (ogrenciListe[i].no == tempNo) {
          ogrenciListe[i].saat += tempSaat;
          break;
        }
      }

    }
    dosyaOku.close();
  }
  ofstream dvdzYaz(dvdzDosya);

  // Haftalık ders saatine göre geçme sınırının hesaplanması
  totalSaat = gelenDers.saat * 14;
  sinirSaat = totalSaat * 0.30;

  // Ogrenci listesindeki öğrencilerin teker teker okunması ve geçme/kalma durumunun kontrolü
  for (size_t i = 0; i < ogrenciListe.size(); i++) {

    if (ogrenciListe[i].saat >= sinirSaat) {
      dvdzYaz << ogrenciListe[i].no << " " << ogrenciListe[i].ad << " " << ogrenciListe[i].soyad << " 0" <<
        endl;
    } else {
      dvdzYaz << ogrenciListe[i].no << " " << ogrenciListe[i].ad << " " << ogrenciListe[i].soyad << " 1" <<
        endl;
    }
  }

  dvdzYaz.close();
}
// Harf notlarının hesaplanması
void DersKoduHarfNotları(Ders gelenDers) {
  // İlgili değişkenlerin tanımlanması
  int araS1, araS2, donemSS, kisaS1, kisaS2, odev1, odev2, proje1, proje2;
  double araS1Y = 0, araS2Y = 0, donemSSY = 0, kisaS1Y = 0, kisaS2Y = 0, odev1Y = 0, odev2Y = 0,
    proje1Y = 0, proje2Y = 0;
  string secim;
  string ara1Dosya = gelenDers.kod + "-" + "ara1Not.txt", finalDosya = gelenDers.kod + "-" +
    "finalNot.txt", ara2Dosya = gelenDers.kod + "-" + "ara2Not.txt", kisa1Dosya = gelenDers.kod + "-" +
    "kisa1Not.txt", kisa2Dosya = gelenDers.kod + "-" + "kisa2Not.txt", odev1Dosya = gelenDers.kod + "-" +
    "odev1Not.txt", odev2Dosya = gelenDers.kod + "-" + "odev2Not.txt", proje1Dosya = gelenDers.kod + "-" +
    "proje1Not.txt", proje2Dosya = gelenDers.kod + "-" + "proje2Not.txt";
  string AktiflikDosya = gelenDers.kod + "Aktiflik.txt";
  // Ders aktiflik dosyasının kontrol edilmesi
  ifstream aktiflikoku(AktiflikDosya);
  if (!aktiflikoku.is_open()) {
    cerr << "Ders Aktiflik Dosyasi Bulunamamistir!" << endl;
    return;
  }
  // Aktiflik dosyasının okunup ilgili değişkenlere tanımlanması
  while (aktiflikoku >> araS1 >> donemSS >> araS2 >> kisaS1 >> kisaS2 >> odev1 >> odev2 >> proje1 >>
    proje2) {
    // Aktif olan derslere göre ders notlarının giriş kontrolü
    if (araS1 == 1) {
      ifstream araS1kontrol(ara1Dosya);
      if (!araS1kontrol.is_open()) {
        cerr << "AraSinav1 notu girilmemistir!" << endl;
        return;
      }
    }
    if (donemSS == 1) {
      ifstream finalkontrol(finalDosya);
      if (!finalkontrol.is_open()) {
        cerr << "Final notu girilmemistir!" << endl;
        return;
      }
    }
    if (araS2 == 1) {
      ifstream araS2kontrol(ara2Dosya);
      if (!araS2kontrol.is_open()) {
        cerr << "AraSinav2 notu girilmemistir!" << endl;
        return;
      }
    }
    if (kisaS1 == 1) {
      ifstream kisaS1kontrol(kisa1Dosya);
      if (!kisaS1kontrol.is_open()) {
        cerr << "KisaSinav1 notu girilmemistir!" << endl;
        return;
      }
    }
    if (kisaS2 == 1) {
      ifstream kisaSinav2kontrol(kisa2Dosya);
      if (!kisaSinav2kontrol.is_open()) {
        cerr << "KisaSinav2 notu girilmemistir!" << endl;
        return;
      }
    }
    if (odev1 == 1) {
      ifstream odev1kontrol(odev1Dosya);
      if (!odev1kontrol.is_open()) {
        cerr << "Odev1 notu girilmemistir!" << endl;
        return;
      }
    }
    if (odev2 == 1) {
      ifstream odev2kontrol(odev2Dosya);
      if (!odev2kontrol.is_open()) {
        cerr << "Odev2 notu girilmemistir!" << endl;
        return;
      }
    }
    if (proje1 == 1) {
      ifstream proje1kontrol(proje1Dosya);
      if (!proje1kontrol.is_open()) {
        cerr << "Proje1 notu girilmemistir!" << endl;
        return;
      }
    }
    if (proje2 == 1) {
      ifstream proje2kontrol(proje2Dosya);
      if (!proje2kontrol.is_open()) {
        cerr << "Proje2 notu girilmemistir!" << endl;
        return;
      }
    }
  }
  // Ogrenci notlarının saklanması için gerekli struct yapısının oluşturulması
  struct Ogr {
    int no;
    string ad;
    string soyad;
    int ara1 = 0;
    int final1 = 0;
    int ara2 = 0;
    int kisa1 = 0;
    int kisa2 = 0;
    int odev1 = 0;
    int odev2 = 0;
    int proje1 = 0;
    int proje2 = 0;
  };
  vector < Ogr > ogrList;
  string yuzdeDosya = gelenDers.kod + "Yuzdelik.txt";
  ifstream yuzdeOku(yuzdeDosya);
  // Sınav yüzdelerinin okunması ve ilgili değişkenlere atanması
  while (yuzdeOku >> araS1Y >> donemSSY >> araS2Y >> kisaS1Y >> kisaS2Y >> odev1Y >> odev2Y >>
    proje1Y >> proje2Y) {}
  // İlgili değişkenlerin tanımlanması
  double ara1N, ara2N, finalN, kisa1N, kisa2N, odev1N, odev2N, proje1N, proje2N;
  int tempNo, tempNot, tempDevam;
  string tempAd, tempSoyad;
  string dvdzDosyasi = gelenDers.kod + "DVDZ.txt";
  ifstream dvdzOku(dvdzDosyasi);
  // Dersin devamlılık dosyasının kontrol edilmesi
  if (!dvdzOku.is_open()) {
    cerr << "DVDZ Dosyan Yok!";
    return;
  }
  string harfDosya = gelenDers.kod + "HarfNotu.txt";
  ofstream harfYaz(harfDosya);
  // Devamsızlık dosyasının okunması ve öğrencilerin oluşturulması
  while (dvdzOku >> tempNo >> tempAd >> tempSoyad >> tempDevam) {
    if (tempDevam == 1) {
      Ogr yeniOgren;
      yeniOgren.no = tempNo;
      yeniOgren.ad = tempAd;
      yeniOgren.soyad = tempSoyad;
      ogrList.push_back(yeniOgren);
    }
    // Eğer öğrenci devamsız ise harf notu dosyasına DZ yazılması
    else if (tempDevam == 0) {
      harfYaz << tempNo << " " << tempAd << " " << tempSoyad << " 0 DZ" << endl;
    }
  }
  // Aktif olan derslerin dosyalarının okunması ve ilgili nesneye atanması
  if (araS1 == 1) {
    ifstream ara1Oku(ara1Dosya);
    while (ara1Oku >> tempNo >> tempAd >> tempSoyad >> tempNot) {
      for (size_t i = 0; i < ogrList.size(); i++) {
        if (ogrList[i].no == tempNo) {
          if (tempNot == -99) {
            ogrList[i].ara1 = 0;
          } else {
            ogrList[i].ara1 = tempNot;
          }
          break;
        }
      }
    }
    ara1Oku.close();
  }
  if (araS2 == 1) {
    ifstream ara2Oku(ara2Dosya);
    while (ara2Oku >> tempNo >> tempAd >> tempSoyad >> tempNot) {
      for (size_t i = 0; i < ogrList.size(); i++) {
        if (ogrList[i].no == tempNo) {
          if (tempNot == -99) {
            ogrList[i].ara2 = 0;
          } else {
            ogrList[i].ara2 = tempNot;
          }
          break;
        }
      }
    }
    ara2Oku.close();
  }
  if (kisaS1 == 1) {
    ifstream kisas1Oku(kisa1Dosya);
    while (kisas1Oku >> tempNo >> tempAd >> tempSoyad >> tempNot) {
      for (size_t i = 0; i < ogrList.size(); i++) {
        if (ogrList[i].no == tempNo) {
          if (tempNot == -99) {
            ogrList[i].kisa1 = 0;
          } else {
            ogrList[i].kisa1 = tempNot;
          }
          break;
        }
      }
    }
    kisas1Oku.close();
  }
  if (kisaS2 == 1) {
    ifstream kisas2Oku(kisa2Dosya);
    while (kisas2Oku >> tempNo >> tempAd >> tempSoyad >> tempNot) {
      for (size_t i = 0; i < ogrList.size(); i++) {
        if (ogrList[i].no == tempNo) {
          if (tempNot == -99) {
            ogrList[i].kisa2 = 0;
          } else {
            ogrList[i].kisa2 = tempNot;
          }
          break;
        }
      }
    }
    kisas2Oku.close();
  }
  if (odev1 == 1) {
    ifstream odev1Oku(odev1Dosya);
    while (odev1Oku >> tempNo >> tempAd >> tempSoyad >> tempNot) {
      for (size_t i = 0; i < ogrList.size(); i++) {
        if (ogrList[i].no == tempNo) {
          if (tempNot == -99) {
            ogrList[i].odev1 = 0;
          } else {
            ogrList[i].odev1 = tempNot;
          }
          break;
        }
      }
    }
    odev1Oku.close();
  }
  if (odev2 == 1) {
    ifstream odev2Oku(odev2Dosya);
    while (odev2Oku >> tempNo >> tempAd >> tempSoyad >> tempNot) {
      for (size_t i = 0; i < ogrList.size(); i++) {
        if (ogrList[i].no == tempNo) {
          if (tempNot == -99) {
            ogrList[i].odev2 = 0;
          } else {
            ogrList[i].odev2 = tempNot;
          }
          break;
        }
      }
    }
    odev2Oku.close();
  }
  if (donemSS == 1) {
    ifstream finalOku(finalDosya);
    while (finalOku >> tempNo >> tempAd >> tempSoyad >> tempNot) {
      for (size_t i = 0; i < ogrList.size(); i++) {
        if (ogrList[i].no == tempNo) {
          if (tempNot == -99) {
            ogrList[i].final1 = 0;
          } else {
            ogrList[i].final1 = tempNot;
          }
          break;
        }
      }
    }
    finalOku.close();
  }
  if (proje1 == 1) {
    ifstream proje1Oku(proje1Dosya);
    while (proje1Oku >> tempNo >> tempAd >> tempSoyad >> tempNot) {
      for (size_t i = 0; i < ogrList.size(); i++) {
        if (ogrList[i].no == tempNo) {
          if (tempNot == -99) {
            ogrList[i].proje1 = 0;
          } else {
            ogrList[i].proje1 = tempNot;
          }
          break;
        }
      }
    }
    proje1Oku.close();
  }
  if (proje2 == 1) {
    ifstream proje2Oku(proje2Dosya);
    while (proje2Oku >> tempNo >> tempAd >> tempSoyad >> tempNot) {
      for (size_t i = 0; i < ogrList.size(); i++) {
        if (ogrList[i].no == tempNo) {
          if (tempNot == -99) {
            ogrList[i].proje2 = 0;
          } else {
            ogrList[i].proje2 = tempNot;
          }
          break;
        }
      }
    }
    proje2Oku.close();
  }
  // öğrenci notlarının teker teker ilgili yüzdelikle çarpılıp hesaplanması
  for (size_t i = 0; i < ogrList.size(); i++) {
    if (araS1 == 1) {
      ara1N = ogrList[i].ara1 * (araS1Y / 100);
    }
    if (donemSS == 1) {
      finalN = ogrList[i].final1 * (donemSSY / 100);
    }
    if (araS2 == 1) {
      ara2N = ogrList[i].ara2 * (araS2Y / 100);
    }
    if (kisaS1 == 1) {
      kisa1N = ogrList[i].kisa1 * (kisaS1Y / 100);
    }
    if (kisaS2 == 1) {
      kisa2N = ogrList[i].kisa2 * (kisaS2Y / 100);
    }
    if (odev1 == 1) {
      odev1N = ogrList[i].odev1 * (odev1Y / 100);
    }
    if (odev2 == 1) {
      odev2N = ogrList[i].odev2 * (odev2Y / 100);
    }
    if (proje1 == 1) {
      proje1N = ogrList[i].proje1 * (proje1Y / 100);
    }
    if (proje2 == 1) {
      proje2N = ogrList[i].proje2 * (proje2Y / 100);
    }
    int ogrBasariNotu = ara1N + finalN + ara2N + kisa1N + kisa2N + odev1N + odev2N +
      proje1N + proje2N;
    // Öğrenci bilgilerinin dosyaya yazdırılması
    // SADECE BURADA PUAN YAZDIRILACAK:
	harfYaz << ogrList[i].no << " " << ogrList[i].ad << " " << ogrList[i].soyad << " " << ogrBasariNotu << " ";
    // Öğrencinin notuna göre harf notunun hesaplanması ve dosyaya yazdırılması
    if (ogrBasariNotu >= 84 && ogrBasariNotu <= 100) {
      harfYaz << ogrBasariNotu << "AA" << endl;
    } else if (ogrBasariNotu >= 77 && ogrBasariNotu < 84) {
      harfYaz << "AB" << endl;
    } else if (ogrBasariNotu >= 71 && ogrBasariNotu < 77) {
      harfYaz << "BA" << endl;
    } else if (ogrBasariNotu >= 66 && ogrBasariNotu < 71) {
      harfYaz << "BB" << endl;
    } else if (ogrBasariNotu >= 61 && ogrBasariNotu < 66) {
      harfYaz << "BC" << endl;
    } else if (ogrBasariNotu >= 56 && ogrBasariNotu < 61) {
      harfYaz << "CB" << endl;
    } else if (ogrBasariNotu >= 50 && ogrBasariNotu < 56) {
      harfYaz << "CC" << endl;
    } else if (ogrBasariNotu >= 46 && ogrBasariNotu < 50) {
      harfYaz << "CD" << endl;
    } else if (ogrBasariNotu >= 40 && ogrBasariNotu < 46) {
      harfYaz << "DC" << endl;
    } else if (ogrBasariNotu >= 33 && ogrBasariNotu < 40) {
      harfYaz << "DD" << endl;
    } else if (ogrBasariNotu < 33) {
      harfYaz << "FF" << endl;
    }
  }
  harfYaz.close();
}
// Harf notu menü fonksiyonu
void harfNotuMenusu(Ders gelenDers) {
  string ayirac = "============================================================";
  string harfNotDosya = gelenDers.kod + "HarfNotu.txt";
  ifstream harfNotkontrol(harfNotDosya);
  // Harf not dosyasının kontrol edilmesi
  // Eğer dosya yok ise harf notu oluşturma fonksiyonun çalıştırılıp hesaplanması
  if (!harfNotkontrol.is_open()) {
    DersKoduHarfNotları(gelenDers);
    harfNotkontrol.close();
  }
  ifstream harfNotuOku(harfNotDosya);
  // Harf notlarını saklamak için gerekli struct yapısı
  struct harfOgr {
    string ad;
    string soyad;
    int no;
    int puan;
    string harfNot;
  };
  // İlgili değişkenlerin tanımlanması
  int tempNo;
  string tempAd, tempSoyad, tempHarfNot;
  int secim;
  int noArama;
  int tempPuan;
  vector < harfOgr > ogrListe;
  // Harf notu dosyasının okunması ve ilgili değişkenlere tanımlanması
  while (harfNotuOku >> tempNo >> tempAd >> tempSoyad >> tempPuan >> tempHarfNot) {
    harfOgr ogrenci;
    ogrenci.no = tempNo;
    ogrenci.ad = tempAd;
    ogrenci.soyad = tempSoyad;
    ogrenci.puan = tempPuan;
    ogrenci.harfNot = tempHarfNot;
    // Açılan öğrencinin vectore eklenmesi
    ogrListe.push_back(ogrenci);
  }
  // Menü döngüsü
  while (true) {
    cout << endl << ayirac << endl;
    cout << "Secili Ders: " << gelenDers.kod << " - " << gelenDers.ad << endl << ayirac << endl <<
      endl;
    cout << "1) Ogrenci Numarasi ile Arama Yapma" << endl;
    cout << "2) Tum Ogrencilerin Harf Notlari" << endl;
    cout << "3) Devamsizliktan Kalan Ogrenci Listesi" << endl;
    cout << "4) Not Ile Kalanlarin Listesi" << endl;
    cout << "5) En Basarili Ilk 3 Ogrenciyi Listele" << endl;
    cout << endl << "Cikis icin '0' i Tuslayiniz" << endl;
    cout << "Yapmak Istediginiz Islemi Seciniz: " << endl;
    cin >> secim;
    if (cin.fail()) {
      cout << "\n=================================" << endl;
      cout << "Lütfen Yapcağınız İşlemin Başndaki Değeri Giriniz!" << endl;
      cout << "=================================" << endl;
      cin.clear();
      cin.ignore(numeric_limits < streamsize > ::max(), '\n');
      continue;
    }
    if (secim == 0) {
      return;
    }
    // Öğrenci numarasına göre öğrenci bilgilerinin gösterilmesi
    else if (secim == 1) {
      cout << endl << ayirac << endl;
      cout << endl << "Lutfen Aramak Istedginiz Ogrencinin Numarasini Giriniz: " << endl;
      cin >> noArama;
      if (cin.fail()) {
        cout << "\n=================================" << endl;
        cout << "Lütfen Yapcağınız İşlemin Başndaki Değeri Giriniz!" << endl;
        cout << "=================================" << endl;
        cin.clear();
        cin.ignore(numeric_limits < streamsize > ::max(), '\n');
        continue;
      }
      for (size_t i = 0; i < ogrListe.size(); i++) {
        if (ogrListe[i].no == noArama) {
          cout << ogrListe[i].no << " - " << ogrListe[i].ad << " " <<
            ogrListe[i].soyad << " - " << ogrListe[i].harfNot << endl;
        }
      }
    }
    // Tüm öğrencilerin bilgilerinin gösterilmesi
    else if (secim == 2) {
      cout << endl << ayirac << endl;
      for (size_t i = 0; i < ogrListe.size(); i++) {
        cout << ogrListe[i].no << " - " << ogrListe[i].ad << 
        " " << ogrListe[i].soyad << " - Puan: " << ogrListe[i].puan << 
        " - " << ogrListe[i].harfNot << endl;
      }
    }
    // Devamsızlıktan kalan öğrencilerin bilgilerinin gösterilmesi
    else if (secim == 3) {
      cout << endl << ayirac << endl;
      for (size_t i = 0; i < ogrListe.size(); i++) {
        if (ogrListe[i].harfNot == "0 DZ") {
          cout << ogrListe[i].no << " - " << ogrListe[i].ad << " " <<
            ogrListe[i].soyad << " - " << ogrListe[i].puan << " - " << ogrListe[i].harfNot << endl;
        }
      }
    }
    // Not ortalaması ile kalan öğrencilerin bilgilerinin gösterilmesi
    else if (secim == 4) {
      cout << endl << ayirac << endl;
      for (size_t i = 0; i < ogrListe.size(); i++) {
        if (ogrListe[i].harfNot == "FF") {
          cout << ogrListe[i].no << " - " << ogrListe[i].ad << " " <<
            ogrListe[i].soyad << " - " << ogrListe[i].puan << " - " << ogrListe[i].harfNot << endl;
        }
      }
    }
     else if (secim == 5) {
		 cout << endl << ayirac << endl;
		 cout << "--- EN YUKSEK PUANLI ILK 3 OGRENCI ---" << endl;
		 
		 vector<harfOgr> siraliListe = ogrListe;
		 for (size_t i = 0; i < siraliListe.size() - 1; i++) {
			for (size_t j = 0; j < siraliListe.size() - i - 1; j++) {
				if (siraliListe[j].puan < siraliListe[j + 1].puan) {
					harfOgr temp = siraliListe[j];
					siraliListe[j] = siraliListe[j + 1];
					siraliListe[j + 1] = temp;
				}	
			}
		}
	
		int limit = (siraliListe.size() < 3) ? siraliListe.size() : 3;
		
		for (int i = 0; i < limit; i++) {
        // Devamsızlıktan kalan (DZ) öğrencilerin dereceye girmesini engellemek için kontrol
        if (siraliListe[i].harfNot != "DZ") {
            cout << i + 1 << ". Derece: " << siraliListe[i].no << " - " 
                 << siraliListe[i].ad << " " << siraliListe[i].soyad 
                 << " - Puan: " << siraliListe[i].puan << " (" << siraliListe[i].harfNot << ")" << endl;
                 } 
         else {
			 limit = ((int)siraliListe.size() < limit + 1) ? (int)siraliListe.size() : limit + 1;
    }
  }
}
}

}
