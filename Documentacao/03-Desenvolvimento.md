
# Materiais
Para a construção do carrinho, foram utilizados: 

  - Chassi de madeira para carrinho do tipo tanque;
  - Quatro rodas (Duas motorizadas e duas rodas bobas);
  - Arduino UNO;
  - Dois sensores de distância;
  - Buzzer Passivo;
  - Dois LEDs vermelhos;
  - Ponte H (L298N);
  - Fios do tipo macho-macho e macho-fêmea;
  - Dois motores DC (3-6V);
  - Pilhas 18650;
  - Suporte para duas pilhas 18650 com interruptor;
  - Protoboard;
  - Módulo de conexão Bluetooth HC-06;
  - Controle e sensor infra-vermelho;
  - Porcas, parafusos, arruelas, etc.

# Desenvolvimento

O projeto teve início em 22 de abril de 2024. A partir dessa data, começamos a discutir sobre peças e métodos de funcionamento, com base na ideia de um carro-tanque controlado remotamente. Como diferencial, queríamos algo que remetesse à infância e fosse, ao mesmo tempo, inovador. Assim, decidimos por fazer um carrinho temático, pensando em um carrinho da Barbie ou da Hello Kitty.

Em 29 de abril, já tínhamos definido o esboço do projeto, as telas de aplicação e uma lista preliminar de componentes. No entanto, devido a problemas com a esteira do tanque, a lista teve que ser alterada, resultando na transformação do projeto em um carrinho de quatro rodas, sendo que duas seriam motorizadas e duas seriam do carrinho original, servindo como rodas bobas.

A primeira montagem do carrinho foi realizada na casa da Júlia, onde David e Gabriela se reuniram para montar o chassi. Nesse encontro, foi descoberto o problema com as esteiras, que vieram de tamanhos diferentes, levando à alteração do modelo original do carrinho. Decidimos quais componentes utilizar para montá-lo, incluindo sensores, faróis de ré, modo turbo e um buzzer que tocaria música.

Em 13 de maio, Izabela, Eduardo e Gabriela conseguiram desenvolver um aplicativo funcional com layout e códigos preliminares para testes.

Em 27 de maio, o projeto do hardware, inicialmente planejado, foi entregue e começamos a montagem. Com o surgimento de novas necessidades, nos reunimos na biblioteca da PUC Minas para testar a montagem inicial do hardware em conjunto. Após muitas tentativas, Júlia e Gabriela conseguiram realizar o primeiro teste nos motores, registrando o momento em vídeo.

Após essa montagem inicial em grupo, Júlia levou o carrinho para casa e iniciou a implementação de todos os sensores, controles de velocidade, Bluetooth e a organização dos componentes no chassi. Quase todos os sensores e o uso do aplicativo foram implementados, faltando apenas o sensor frontal e o controle de velocidade. Em 22 de junho, após ter sucesso na implementação dos adereços finais, Júlia descobriu que o Bluetooth estava estragado e não haveria tempo para substituí-lo. Com as pilhas também dando instabilidade ao carrinho, a solução encontrada foi utilizar um controle acionado por infravermelho do kit de montagem Arduino. Felizmente, essa opção funcionou, embora a suposta falta de bateria nas pilhas causasse problemas de resposta quando o carrinho era ligado a uma fonte externa. No entanto, ao conectar o Arduino à fonte do computador, funcionava corretamente.

Como resultado final, obtivemos um carrinho controlado remotamente, equipado com sensores frontais e traseiros que permitem parar a uma certa distância de objetos. Implementamos com sucesso a função de tocar música e adicionamos luzes de ré.

Quanto ao aplicativo, o layout e os códigos foram ajustados para garantir uma comunicação eficiente com o carrinho. Apesar dos problemas enfrentados, registramos todo o processo, com vídeos mostrando seu funcionamento pleno e a adaptação ao controle por infravermelho.

## Desenvolvimento do Aplicativo

### Interface
O principal objetivo ao desenvolver o layout foi alinhar-se à temática central do grupo, que incorpora a ideia de um "Monster Truck" com uma abordagem simultaneamente robusta e cativante, evocando reminiscências da infância feminina através de músicas como as da Barbie e da Hello Kitty. Com isso em mente, o design do aplicativo foi concebido em uma paleta de tons variados de rosa.

## Desenvolvimento do Hardware, Código e Montagem

Eduardo e Gabriela iniciaram o projeto esboçando os códigos nas principais ferramentas utilizadas: o MIT App Inventor para o aplicativo de controle no celular e o Arduino IDE para o controle do carrinho.

A montagem do aplicativo e do chassi enfrentou diversos desafios. A ideia inicial era criar um tanque de guerra controlado remotamente. No entanto, surgiram problemas com uma das esteiras, pois havia uma divergência no tamanho das mesmas. Isso impossibilitou o uso das esteiras, levando o grupo a optar por uma solução alternativa: substituir as esteiras por rodas com tração traseira, permitindo o movimento normal do carrinho. A montagem foi realizada em etapas, conforme a necessidade das peças.

O código foi uma das partes mais desafiadoras do projeto. Modelos iniciais foram criados antes mesmo da construção do carrinho, mas surgiram novas necessidades, como o uso de uma ponte H e configurações adicionais para o Bluetooth. O código foi sendo aprimorado conforme o desenvolvimento do projeto avançava.

Inicialmente, o código contava apenas com a lógica das direções. Em seguida, foram adicionadas linhas para viabilizar a conexão Bluetooth, ativar as funcionalidades dos sensores, do buzzer e, finalmente, acender os LEDs. O desenvolvimento do código foi trabalhoso, mas alcançou os resultados esperados.

Após os testes iniciais dos motores e do Bluetooth, foram implementadas as funções de controle do carrinho para frente, trás, esquerda e direita. Em seguida, foi adicionado o primeiro sensor de distância traseira, juntamente com dois LEDs que simulavam faróis de ré. A função musical também foi implementada. Com tudo funcionando, o próximo passo foi adicionar o controle de velocidade para criar um modo turbo e mais um sensor de distância na frente do carrinho.

Devido a problemas com o funcionamento do Bluetooth, foi necessário criar um novo código onde as funções do carrinho são controladas pelos botões de um controle infravermelho.

## Comunicação entre App e Hardware

Dentre as funcionalidades do MIT App Inventor, existe a ferramenta “ClienteBluetooth” e "Temporizador" que permite a comunicação de dados entre o celular e o microcontrolador por meio de ondas de alta frequência (UHF). Dessa forma, dados sobre o aperto de um dos botões no aplicativo de celular ou em um controle remoto são enviados para o arduino que, por fim, responde aos comandos. Assim, os dados coletados pelo controle direcional dentro do MIT App Inventor são utilizados para mudar a rotação das rodas controladas pelo arduino. Para que isso funcione, no código foi implementada a biblioteca SoftwareSerial.h que nos permite configurar as entradas e saídas do bluetooth e suas ações correspondentes. Algo próximo acontece com o controle infra-vermelho, onde foi inciada a biblioteca IRremote.hpp, que nos permite indicar os endereços dos botões acionados no controle e realizar ações correspondentes.
