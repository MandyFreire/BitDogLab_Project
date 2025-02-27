# BitDogLab_Project
Monitoramento e Otimização Inteligente do Consumo de Energia Residencial


1. Escopo do Projeto
   
1.1. Apresentação do Projeto
Este projeto visa desenvolver um sistema inteligente para monitoramento e otimização do consumo de energia em residências e escritórios. Utilizando sensores de corrente não invasivos (CT clamp ) e a placa BitDogLab,  o sistema coleta dados em tempo real, permitindo a análise detalhada dos padrões de consumo e sugerindo melhorias para a economia de energia.

1.2. Título do Projeto
Monitoramento Inteligente de Energia com BitDogLab

1.3. Objetivos do Projeto
•	Objetivo Geral: Desenvolver um sistema de monitoramento energético para analisar e otimizar o consumo elétrico de ambientes residenciais e comerciais.
•	Objetivos Específicos: 
o	Medir e exibir o consumo de energia em tempo real;
o	Enviar alertas sobre consumo elevado;
o	Integrar com dispositivos IoT para automação e controle remoto;
o	Implementar um dashboard para visualização dos dados.

1.4. Descrição do Funcionamento
O sistema capta os dados de consumo através dos sensores de corrente conectados à BitDogLab. Os dados são processados e enviados via Wi-Fi para um servidor na nuvem (ThingSpeak ). Um dashboard exibe gráficos e informações detalhadas sobre o consumo, permitindo a análise e controle remoto dos dispositivos elétricos.

1.5. Justificativa
A crescente demanda por eficiência energética torna essencial o uso de soluções inteligentes para o controle do consumo elétrico. Este projeto permite que usuários monitorem e otimizem seu consumo, reduzindo custos e impactos ambientais.

1.6. Originalidade
Este projeto diferencia-se por integrar sensores não invasivos com análise de consumo em tempo real, automação IoT e aprendizado de máquina para previsão de desperdícios, algo pouco explorado em soluções acessíveis para residências.
 
2. Especificação do Hardware
2.1. Diagrama em Bloco
 ![image](https://github.com/user-attachments/assets/51c73e50-d43f-4ebf-8003-237e0df6eb75)

2.2. Função de Cada Bloco
•	Sensor de Corrente (CT Clamp): Captura a corrente elétrica do circuito monitorado.
•	BitDogLab: Processa os dados e transmite via Wi-Fi.
•	Servidor Cloud: Armazena e processa os dados coletados.
•	Dashboard: Exibe informações e alertas para o usuário.

2.3. Configuração dos Blocos
Cada sensor será calibrado para fornecer medições precisas. A BitDogLab será configurada para capturar os dados a cada 10 segundos e transmiti-los para a nuvem.

2.4. Descrição da Pinagem Usada
•	Entrada ADC: Sensor de corrente ligado ao pino analógico da BitDogLab.
•	Wi-Fi: Configurado para conexão com o servidor MQTT.
Obs. Para fins de testes, ao invés do sensor de corrente, foi utilizado um potenciômetro para variação.

2.5. Circuito Completo do Hardware
Para fins de testes, o hardware preliminar é simulado na plataforma wooki e o sensor utilizado é um potenciômetro. Segue esquemático de teste:
 
3. Testes e Validação
3.1. Teste de Precisão
Procedimento: Comparar os valores medidos pelo sistema com um medidor comercial certificado ao longo de 24 horas.
Resultado Esperado: Diferença máxima de 5% entre as medições.

3.2. Teste de Latência
Procedimento: Avaliar o tempo entre a captação dos dados e sua exibição no dashboard.
Resultado Esperado: Tempo máximo de 2 segundos para transmissão e exibição dos dados.

3.3. Teste de Consumo Energético
Procedimento: Medir o consumo da BitDogLab e seus sensores durante 24 horas de funcionamento.
Resultado Esperado: Consumo inferior a 5W para minimizar impacto na conta de energia.

3.4. Teste de Segurança Wi-Fi
Procedimento: Verificar se os dados transmitidos estão criptografados usando ferramentas de análise de pacotes.
Resultado Esperado: Confirmação da transmissão de dados segura (criptografia WPA2 ou superior).
 
4. Execução do Projeto
4.1. Metodologia
•	Pesquisa sobre monitoramento de energia;
•	Escolha do hardware adequado;
•	Desenvolvimento da programação;
•	Implementação e testes.

4.2. Testes de Validação
Os testes descritos na seção anterior serão aplicados para garantir o funcionamento correto do sistema.

4.3. Discussão dos Resultados
Análise dos testes realizados e identificação de melhorias futuras.

4.3.1 Aprimoramento da Precisão das Medições
A adoção de sensores de corrente de maior precisão, bem como a implementação de algoritmos de calibração automática, pode melhorar significativamente a confiabilidade dos dados coletados. Métodos de filtragem digital, como Média Móvel ou Filtro Kalman, podem ser aplicados para minimizar interferências e ruídos nos sinais captados.

4.3.2 Avanços na Comunicação e Conectividade
A substituição do protocolo HTTP pelo MQTT pode reduzir o consumo de banda e aumentar a eficiência do envio de dados. Adicionalmente, a implementação de comunicação local via Bluetooth ou LoRa ampliaria a aplicabilidade do sistema para ambientes sem conectividade Wi-Fi.

4.3.3 Evolução do Dashboard e Interface do Usuário
A criação de um dashboard personalizado, em substituição ao ThingSpeak, pode fornecer uma experiência mais interativa e informativa ao usuário. Além disso, a integração com assistentes virtuais, como Alexa e Google Assistant, permitiria a consulta por voz das informações de consumo energético.

4.3.4 Implementação de Inteligência Artificial
O uso de aprendizado de máquina possibilitaria a identificação de padrões de consumo e a detecção de anomalias, permitindo sugestões personalizadas para economia de energia. Técnicas como NILM (Non-Intrusive Load Monitoring) poderiam ser utilizadas para identificar quais aparelhos estão consumindo mais energia sem a necessidade de sensores adicionais.

4.3.5 Expansão para Novas Aplicações
A integração do sistema com fontes de energia renovável, como painéis solares, permitiria o monitoramento tanto do consumo quanto da geração de energia. Além disso, sua aplicação pode ser estendida para ambientes industriais, auxiliando no gerenciamento energético de grandes instalações.

5. Referências
•	Normas ABNT NBR 5410:2004 e ISO 50001:2018.
•	Documentação da BitDogLab.
•	CT Clamp Current Sensor — ESPHome
•	BitDogLab
•	IoT Analytics - ThingSpeak Internet of Things
