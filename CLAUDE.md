# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 목적

알고리즘 및 코딩테스트 개념 정리·복습용 레포지토리. 주제별로 Visual Studio C++ 프로젝트와 git 브랜치를 분리하여 관리한다.

## Claude의 역할

- 알고리즘 개념 설명 및 예시 소스코드 작성 (`.cpp`)
- 프로젝트 단위로 개념 정리 마크다운 파일 (`.md`) 생성 — Gemini가 이 파일을 Notion에 업로드함
- Notion 연동 및 업로드는 **Gemini의 역할** (`GEMINI.md` 참고). Claude는 관여하지 않음

## 빌드

```powershell
# 솔루션 전체 빌드
msbuild AlgoritmStudy.sln /p:Configuration=Debug /p:Platform=x64

# 특정 프로젝트만 빌드
msbuild Dijkstra_01\Dijkstra_01.vcxproj /p:Configuration=Debug /p:Platform=x64
```

빌드 결과물은 `x64\Debug\` 아래에 생성된다.

## 프로젝트 구조

```
AlgoritmStudy.sln          # Visual Studio 솔루션 (모든 주제 포함)
AlgoritmStudy/             # 기초 빌드용 베이스 (main 브랜치)
Dijkstra_01/               # 다익스트라 (Dijkstra 브랜치)
  ├── Dijkstra_01.cpp      # 개념 설명(주석) + 예시 코드
  └── Dijkstra_01.md       # Gemini용 Notion 업로드 문서
```

## 새 주제 추가 시 작업 순서

1. 주제명으로 git 브랜치 생성 (예: `BFS`, `DP`)
2. `AlgoritmStudy.sln`에 새 VS 프로젝트 추가 (`주제명_01.vcxproj`, 프리컴파일드 헤더 미사용)
3. `주제명_01.cpp` — 개념 설명 주석 + 컴파일 가능한 예시 코드 작성
4. `주제명_01.md` — Gemini용 문서 작성 (아래 Front Matter 형식 준수)

## MD 파일 Front Matter 형식

```markdown
---
title: "주제명"
category: "코딩테스트 / 알고리즘"
tags: ["알고리즘", "태그"]
---
```

Notion 카테고리별 DB ID는 `GEMINI.md`에 정의되어 있음.