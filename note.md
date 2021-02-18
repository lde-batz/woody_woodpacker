DOC:
 - http://www.stonedcoder.org/~kd/lib/61-267-1-PB.pdf
 x https://packetstormsecurity.com/files/12327/elf-pv.txt.html
 x https://ensiwiki.ensimag.fr/images/b/b2/ENSIMAG-2A-Securiy-Cryptology-2016-Graux-Mouillard-Saoud.pdf
 x http://phrack.org/issues/58/5.html#article
 - https://grugq.github.io/docs/subversiveld.pdf

La compression exécutable est tout moyen de compresser un fichier exécutable et de combiner les données compressées avec un code de décompression en un seul exécutable.
Lorsque cet exécutable compressé est exécuté, le code de décompression recrée le code d'origine à partir du code compressé avant de l'exécuter.
Dans la plupart des cas, cela se produit de manière transparente afin que l'exécutable compressé puisse être utilisé exactement de la même manière que l'original.
Les compresseurs exécutables sont souvent appelés "runtime packers", "software packers", "software protectors" (ou meme "polymorphic packers" et "obfuscating tools").

dans le header elf:
 	il faut check si dans le header e_ehsize = Elf32_Ehdr et donc si le header fait la taille de e_ehsize
	il faut check que e_phentsize = Elf32_Phdr
	il faut check que e_shentsize = Elf32_Shdr

dans le header de section (Elf32_Shdr)
	sh_entsize permet de verifier des erreurs

dans le header de segment (Elf32_Phdr)
	

methode de chiffrement:
	OR: caca
	Stream Ciphers: nice pour les bianires
	Block Ciphers: bof pour les binaires
	Virtual CPUs: bien pour les binaires mais galere

Dacryfile:
	chiffre du debut de la section .text a la fin du segment .text
	Le fichier hôte est chiffré du début de la section .text à la fin du segment .text.
	Le fichier a maintenant son code objet et ses données protégées en lecture seule par cryptage, alors que toutes ses données et objets dynamiques sont ouvert à l'inspection.
	Le fichier hôte est injecté avec un parasite qui va effectuer le décryptage d'exécution.
	Ce parasite peut être de taille arbitraire car il est ajouté à la fin du segment .data.

Packing ELF:
	L'approche la plus flexible pour envelopper un exécutable a été inventée par le développeurs du packer UPX.
	Ils chargent le binaire dans l'espace utilisateur, tout comme le noyau le fait.
	Une fois fait correctement il n'y a pas de changement visible de comportement du programme encapsulé. 


On mets le parasite a la fin du segmet .text (ex: entre le segment 1 et 2)
En-tête ELF
  Tableau d'en-tête de programme
  Segment 1 - Le segment de texte de l'hôte
      - Le parasite
  Segment 2
  Tableau des en-têtes de section
  Section 1
  ...
  ...
  Section n

Cependant les adresses virtuelles des composants ulterieurs doivent etre modifie pour coller avec leurs nouvel emplacement.

Insérer du code à la fin du segment de texte nous laisse donc la chose suivante à faire jusqu'à présent.

  * Augmentez p_shoff pour tenir compte du nouveau code dans l'en-tête ELF
  * Localisez l'en-tête du programme du segment de texte
    * Augmentez p_filesz pour tenir compte du nouveau code
    * Augmentez p_memsz pour tenir compte du nouveau code
  * Pour chaque phdr dont le segment est après l'insertion (segment de texte)
    * augmenter p_offset pour refléter la nouvelle position après l'insertion
  * Pour chaque shdr dont la section réside après l'insertion
    * Augmentez sh_offset pour tenir compte du nouveau code
  * Insérez physiquement le nouveau code dans le fichier - segment de texte p_offset + p_filesz (original)


L'algorithme final a utilise est:

  * Augmentez p_shoff de PAGE_SIZE dans l'en-tête ELF
  * Patch le code d'insertion (parasite) pour sauter au point d'entrée (original)
  * Localisez l'en-tête du programme du segment de texte
    * Modifiez le point d'entrée de l'en-tête ELF pour pointer vers le nouveau code (p_vaddr + p_filesz)
    * Augmenter p_filesz par compte pour le nouveau code (parasite)
    * Augmenter p_memsz pour tenir compte du nouveau code (parasite)
  * Pour chaque phdr dont le segment est après l'insertion (segment de texte)
    * augmenter p_offset de PAGE_SIZE
  * Pour le dernier shdr dans le segment de texte
    * augmenter sh_len de la longueur du parasite
  * Pour chaque shdr dont la section réside après l'insertion
    * Augmenter sh_offset de PAGE_SIZE
  * Insérez physiquement le nouveau code (parasite) et le pad à PAGE_SIZE, dans le fichier - segment de texte p_offset + p_filesz (original)

Il est fortement suggéré de ne pas utiliser de rodata, en fait, il est fortement suggéré de ne pas utiliser du tout de données spécifiques à un emplacement résidant à l'extérieur du parasite au moment de l'infection.

L'utilisation de tout appel de bibliothèque partagée à partir du parasite doit être supprimée, pour éviter tout problème de liaison et pour maintenir un parasite portable dans les fichiers qui utilisent des bibliothèques différentes (pas de libc).

Plus important encore, le code parasite doit être déplaçable.
Il est possible de patcher le code parasite avant de l'insérer, mais l'approche la plus propre consiste à écrire du code qui n'a pas besoin d'être patché.









Les binaires de porte dérobée peuvent être divisés en trois problèmes: créer une charge utile, l'injecter dans les binaires et rediriger le flux d'exécution vers la charge utile.
Dans cet article, nous traitons du second: écrire du code, nommé payload, dans un programme déjà compilé.
Pour les autres parties, beaucoup de charge utile peut être trouvée sur le web [7] et la redirection de flux est bien documentée [2] [3] [4].

Un exécutable ELF a toujours un segment de type «load».

En général, la table d'en-tête de programme est placée juste après l'en-tête de fichier.
Ensuite, toutes les données sont placées et le fichier se termine par le tableau des en-têtes de section.












