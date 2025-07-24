# RTOS_smart_wine_celler

> **2025년 HARMAN Semicon Academy 1기** <br/> **개발기간: 2025.06.03 ~ 06.12**

## 개발팀 소개

|박호윤                                          |박지수                                            |임윤재                                         |함영은                                      |                                                                               
| :--------------------------------------------: | :--------------------------------------------:     | :---------------------------------------:       | :---------------------------------------: |
|   [@cong2738](https://github.com/cong2738)     |    [@Friday930](https://github.com/Friday930)      | [@immune](https://github.com/immune1029)        | [@heyhoo46](https://github.com/heyhoo46)  |
|SystenArchitecture Design And GAME LOGIC Circuit Develop           |ISP Develop and SIM,VGA Print module develop And SIM|camera communication develop and Game font design|GAME UI design, Graphic Circuit develop, GameLogic SIM|

## Introduce

- RTOS_smart_wine_celler:</br>  RTOS를 적용한 스마트 와인셀러.
- RTOS를 이용한 멀티스레딩을 통해 센서, 버튼 등 다양한 입력을 실시간적으로 동시에 수행하며 처리하는 센서 인터페이스 펌웨어를 설계한다.
- IPO Model과 Producer/Contumer DesignPattern을 적용하여 확장성과 협업에 용이하게 설계한다.

## Stacks

### Environment
![STMCubeIDE](https://img.shields.io/badge/Tool-STMCubeIDE-904cab?style=for-the-badge&logo=&logoColor=#2C2255)

### Simulation Visualizing
![C](https://img.shields.io/badge/Lang-C-A8B9CC?style=for-the-badge)</br>

### Board
![stm32h7xx](https://img.shields.io/badge/Board-stm32h7xx-03234B?style=for-the-badge)</br>
![ARM Cortex M-7](https://img.shields.io/badge/Core-ARM_Cortex_M7-0091BD?style=for-the-badge)</br>

## Object Diagram

<img width="321" height="241" alt="와인냉장고 설계-ob_dia drawio" src="https://github.com/user-attachments/assets/e9babd54-f41f-4eac-a8b3-618bcc171223" />
</br>

_ _ _ _ _ _

### Project Overview

#### Software Stack

<img width="651" height="301" alt="와인냉장고 설계-sw_stacj drawio" src="https://github.com/user-attachments/assets/b8adc136-f62b-4d30-9d21-df6c6e73b241" />
</br>

#### Design Pattern

- IPO Model</br>
  - APP를 입력, 처리, 출력 계층으로 분리 및 격리 인과 요인을 통제하여 프로젝트 시각화에 도움을 준다.</br>
  - 목적: 프로젝트를 방법론에 따라 구분하고, 프로세스 단계와 그 이유를 명확히 한다. 그를 통해 구조 이해를 높혀 팀원간 협력에 도움을 준다.</br>
   <img width="auto" height="auto" alt="image" src="https://github.com/user-attachments/assets/b9bb38c6-70a1-4cc6-ac12-6103c29daea1" /></br>
- Producer–Consumer Pattern</br>
  - 전 단계 모듈에서 처리후 저장(throw), 다음 단계 모듈에서 데이터를 가져가는(Get) 구조</br>
  - 이점: 컨슈머 입장에서 프로듀서의 구조, 로직을 신경쓰지 않고 데이터만 가져가도록 설계, 모듈간 역할 구분을 뚜렷하게 할 수 있다.</br>
  - 주의사항: 프로듀서와 컨슈머간 싱크로나이즈가 틀어질 경우 쓰레기값이 컨슈머에게 전달 될 위험이 있다</br>
<img width="auto" height="auto" alt="와인냉장고 설계-Producer–Consumer 패턴 drawio" src="https://github.com/user-attachments/assets/bb4e4853-409c-4bdf-9870-52c80ec4d9cc" /></br>
<img width="801" height="431" alt="와인냉장고 설계-qkqk drawio" src="https://github.com/user-attachments/assets/9ee2135b-b035-40d2-a928-b2f953be3a36" /></br>


#### Sequence Diagram

<img width="961" height="549" alt="와인냉장고 설계-seq_dai drawio" src="https://github.com/user-attachments/assets/ffbb2f68-d719-4b37-b4ef-ddd8f60efe42" /></br>

   
_ _ _ _ _ _

## video  
click!--></br>
<img width="426" height="240" alt="image" src="https://github.com/user-attachments/assets/301a0f72-d0db-416d-9c61-74eb544f039e" /></br>
<img width="426" height="240" alt="image" src="https://github.com/user-attachments/assets/2c0d86da-2f75-44ac-9335-3ed33a637c69" /></br>
<img width="426" height="240" alt="image" src="https://github.com/user-attachments/assets/22107dc3-5c11-4185-820a-989a9f89e10d" /></br>
