
# Materiais

Para a construção do carrinho, foram utilizados: 
Um chassi de madeira, quatro rodas, um Arduino, dois sensores, dois LEDs, uma ponte H, fios de conexão, dois motores, pilhas, uma protoboard e um módulo de conexão Bluetooth, além de porcas e parafusos para manter o carrinho estável.

# Desenvolvimento
O projeto teve início em 22 de abril de 2024. A partir dessa data, começamos a discutir sobre peças e métodos de funcionamento, com base na ideia de um carro-tanque controlado remotamente. Como diferencial, queríamos algo que remetesse à infância e fosse, ao mesmo tempo, inovador. Assim, decidimos incorporar música utilizando um buzzer e adicionar um modo turbo.
Em 29 de abril, já tínhamos definido o esboço do projeto, as telas de aplicação e uma lista preliminar de componentes. No entanto, devido a problemas com a esteira do tanque, a lista teve que ser alterada, resultando na transformação do projeto em um carrinho de quatro rodas.
Em 13 de maio, conseguimos desenvolver um aplicativo funcional com um layout e códigos preliminares para testes.
Em 27 de maio, o projeto do hardware, inicialmente planejado, foi entregue e começamos a montagem. No entanto, com o surgimento de novas necessidades, aprimoramos os componentes utilizados.
Como resultado final, obtivemos um carrinho controlado remotamente, equipado com sensores frontais e traseiros que permitem ao carrinho parar a uma certa distância de objetos. Implementamos com sucesso a função de tocar música e adicionamos luzes de ré.
Quanto ao aplicativo, o layout e os códigos foram ajustados para garantir uma comunicação eficiente com o carrinho.

## Desenvolvimento do Aplicativo

### Interface
O principal objetivo ao desenvolver o layout foi alinhar-se à temática central do grupo, que incorpora a ideia de um "Monster Truck" com uma abordagem simultaneamente robusta e cativante, evocando reminiscências da infância feminina através de músicas como as da Barbie e da Hello Kitty. Com isso em mente, o design do aplicativo foi concebido em uma paleta de tons variados de rosa.

### Código
Inicialmente, um membro do grupo fez um esboço dos códigos dentro das principais ferramentas utilizadas na formação desse projeto. Para o aplicativo de celular, o MIT App Inventor e, para o controle do carrinho, o ambiente de desenvolvimento integrado Arduino.ide.
Na próxima versão, outros integrantes do trabalho aprimoraram e adicionaram mais ferramentas e funcionalidades a esse código base. O processo de desenvolvimento passou por diversas tentativas e erros até que conseguimos alcançar o resultado final.

## Desenvolvimento do Hardware

### Montagem

A montagem do aplicativo enfrentou diversos desafios, além de erros e acertos. A ideia inicial era criar algo similar a um tanque de guerra controlado remotamente; entretanto, houve um problema com uma das esteiras que transformaria o carrinho em um tanque. Devido à divergência no tamanho das esteiras, tivemos que optar por uma solução alternativa para permitir que o carrinho funcionasse. A conclusão do grupo foi substituir as esteiras por rodas com tração traseira, permitindo que o carrinho se movimentasse normalmente.
A montagem foi realizada em etapas, de acordo com a necessidade das peças.

### Desenvolvimento do Código

Descreva como foi o desenvolvimento do código do arduino/ESP.

## Comunicação entre App e Hardware

Dentre as funcionalidades do MIT App Inventor, existe a ferramenta “ClienteBluetooth” que permite a comunicação de dados entre o celular e o microcontrolador por meio de ondas de alta frequência (UHF). Dessa forma, dados sobre o aperto de um dos botões no aplicativo de celular ou em um controle remoto são enviados para o arduino que, por fim, responde aos comandos. Assim, os dados coletados pelo controle direcional dentro do MIT App Inventor são utilizados para mudar a rotação das rodas controladas pelo arduino.
