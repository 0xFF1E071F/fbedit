GetFileIDFromProjectFileID		PROTO	:DWORD
AnyBreakPoints					PROTO

.code

DecToBin proc uses ebx esi,lpStr:DWORD
	LOCAL	fNeg:DWORD

    mov     esi,lpStr
    mov		fNeg,FALSE
    mov		al,[esi]
    .if al=='-'
		inc		esi
		mov		fNeg,TRUE
    .endif
    xor     eax,eax
  @@:
    cmp     byte ptr [esi],30h
    jb      @f
    cmp     byte ptr [esi],3Ah
    jnb     @f
    mov     ebx,eax
    shl     eax,2
    add     eax,ebx
    shl     eax,1
    xor     ebx,ebx
    mov     bl,[esi]
    sub     bl,30h
    add     eax,ebx
    inc     esi
    jmp     @b
  @@:
	.if fNeg
		neg		eax
	.endif
    ret

DecToBin endp

IsDec proc uses esi,lpStr:DWORD

	mov		esi,lpStr
	.if byte ptr [esi]=='-'
		inc		esi
	.endif
	.while TRUE
		mov		al,[esi]
		.if al>='0' && al<='9'
		.elseif !al || al==']'
			mov		eax,esi
			sub		eax,lpStr
			jmp		Ex
		.else
			.break
		.endif
		inc		esi
	.endw
	xor		eax,eax
  Ex:
	ret

IsDec endp

HexToBin proc uses esi,lpStr:DWORD

	mov		esi,lpStr
	xor		edx,edx
	.while byte ptr [esi]
		mov		al,[esi]
		.if al>='0' && al<='9'
			sub		al,'0'
		.elseif al>='A' && al<='F'
			sub		al,'A'-10
		.elseif al>='a' && al<='f'
			sub		al,'a'-10
		.else
			jmp		Ex
		.endif
		shl		edx,4
		or		dl,al
		inc		esi
	.endw
  Ex:
	mov		eax,edx
    ret

HexToBin endp

IsHex proc uses esi,lpStr:DWORD

	mov		esi,lpStr
	.while byte ptr [esi]
		mov		al,[esi]
		.if al>='0' && al<='9' || al>='A' && al<='F' || al>='a' && al<='f'
		.elseif (al=='h' || al=='H') && (!byte ptr [esi+1] || byte ptr [esi+1]==']')
			mov		eax,esi
			sub		eax,lpStr
			jmp		Ex
		.else
			.break
		.endif
		inc		esi
	.endw
	xor		eax,eax
  Ex:
	ret

IsHex endp

AnyToBin proc lpStr:DWORD

	invoke IsHex,lpStr
	.if eax
		invoke HexToBin,lpStr
		mov		edx,eax
		mov		eax,TRUE
		jmp		Ex
	.else
		invoke IsDec,lpStr
		.if eax
			invoke DecToBin,lpStr
			mov		edx,eax
			mov		eax,TRUE
			jmp		Ex
		.endif
	.endif
	xor		edx,edx
	xor		eax,eax
  Ex:
	ret

AnyToBin endp

PutString proc lpString:DWORD

	invoke SendMessage,hOut1,EM_REPLACESEL,FALSE,lpString
	invoke SendMessage,hOut1,EM_REPLACESEL,FALSE,addr szCR
	invoke SendMessage,hOut1,EM_SCROLLCARET,0,0
	ret

PutString endp

PutStringOut proc lpString:DWORD,hWin:HWND

	invoke SendMessage,hWin,EM_REPLACESEL,FALSE,lpString
	invoke SendMessage,hWin,EM_REPLACESEL,FALSE,addr szCR
	invoke SendMessage,hWin,EM_SCROLLCARET,0,0
	ret

PutStringOut endp

HexByte proc

	mov		ah,al
	shr		al,4
	and		ah,0Fh
	.if al<=9
		add		al,30h
	.else
		add		al,41h-0Ah
	.endif
	.if ah<=9
		add		ah,30h
	.else
		add		ah,41h-0Ah
	.endif
	ret

HexByte endp

HexDWORD proc uses ebx edi,lpBuff:DWORD,Val:DWORD

	mov		edi,lpBuff
	mov		ebx,Val
	xor		ecx,ecx
	.while ecx<4
		rol		ebx,8
		mov		eax,ebx
		invoke HexByte
		mov		[edi],ax
		inc		edi
		inc		edi
		inc		ecx
	.endw
	mov		byte ptr [edi],0
	ret

HexDWORD endp

DumpLine proc uses ebx esi edi,hWin:HWND,nAdr:DWORD,lpDumpData:DWORD,nBytes:DWORD
	LOCAL	buffer[256]:BYTE

	mov		ebx,nAdr
	mov		esi,lpDumpData
	lea		edi,buffer
	xor		ecx,ecx
	.while ecx<4
		rol		ebx,8
		mov		eax,ebx
		invoke HexByte
		mov		[edi],ax
		inc		edi
		inc		edi
		inc		ecx
	.endw
	mov		byte ptr [edi],' '
	inc		edi
	xor		ecx,ecx
	.while ecx<nBytes
		mov		al,[esi+ecx]
		invoke HexByte
		mov		[edi],ax
		inc		edi
		inc		edi
		.if ecx==7
			mov		byte ptr [edi],'-'
		.else
			mov		byte ptr [edi],' '
		.endif
		inc		edi
		inc		ecx
	.endw
	mov		ecx,16
	sub		ecx,nBytes
	.while ecx
		mov		dword ptr [edi],'   '
		add		edi,3
		dec		ecx
	.endw
	xor		ecx,ecx
	.while ecx<nBytes
		mov		al,[esi+ecx]
		.if al<20h || al>=80h
			mov		al,'.'
		.endif
		mov		[edi],al
		inc		edi
		inc		ecx
	.endw
	mov		dword ptr [edi],0A0Dh
	invoke SendMessage,hWin,EM_REPLACESEL,FALSE,addr buffer
	ret

DumpLine endp

EnableMenu proc uses esi edi
	LOCAL	hREd:HWND
	LOCAL	chrg:CHARRANGE
	LOCAL	nLine:DWORD
	LOCAL	nInx:DWORD

	mov		esi,offset IDAddIn+4
	mov		eax,lpData
	.if [eax].ADDINDATA.fProject && !fNoDebugInfo
		; Toggle &Breakpoint
		invoke EnableMenuItem,hMnu,[esi],MF_BYCOMMAND or MF_GRAYED
		; Run &To Caret
		invoke EnableMenuItem,hMnu,[esi+24],MF_BYCOMMAND or MF_GRAYED
		mov		eax,lpHandles
		.if [eax].ADDINHANDLES.hEdit
			mov		edx,[eax].ADDINHANDLES.hEdit
			mov		hREd,edx
			invoke GetWindowLong,[eax].ADDINHANDLES.hMdiCld,0
			.if eax==ID_EDIT
				.if dbg.hDbgThread
					invoke SendMessage,hREd,EM_EXGETSEL,0,addr chrg
					invoke SendMessage,hREd,EM_EXLINEFROMCHAR,0,chrg.cpMin
					mov		nLine,eax
					mov		eax,lpHandles
					invoke GetWindowLong,[eax].ADDINHANDLES.hMdiCld,16
					invoke GetFileIDFromProjectFileID,eax
					.if eax
						mov		edx,nLine
						inc		edx
						xor		ecx,ecx
						mov		edi,dbg.hMemLine
						.while ecx<dbg.inxline
							.if edx==[edi].DEBUGLINE.LineNumber
								.if ax==[edi].DEBUGLINE.FileID
									.break
								.endif
							.endif
							inc		ecx
							add		edi,sizeof DEBUGLINE
						.endw
						.if ecx!=dbg.inxline
							; Toggle &Breakpoint
							invoke EnableMenuItem,hMnu,[esi],MF_BYCOMMAND or MF_ENABLED
							; Run &To Caret
							invoke EnableMenuItem,hMnu,[esi+24],MF_BYCOMMAND or MF_ENABLED
						.endif
					.endif
				.else
					; Toggle &Breakpoint
					invoke EnableMenuItem,hMnu,[esi],MF_BYCOMMAND or MF_ENABLED
				.endif
			.endif
		.endif
		; &Clear Breakpoints
		invoke AnyBreakPoints
		.if eax
			invoke EnableMenuItem,hMnu,[esi+4],MF_BYCOMMAND or MF_ENABLED
		.else
			invoke EnableMenuItem,hMnu,[esi+4],MF_BYCOMMAND or MF_GRAYED
		.endif
		; &Run
		invoke EnableMenuItem,hMnu,[esi+8],MF_BYCOMMAND or MF_ENABLED
		; Do not Debug
		invoke EnableMenuItem,hMnu,[esi+28],MF_BYCOMMAND or MF_ENABLED
		.if dbg.hDbgThread
			; &Stop
			invoke EnableMenuItem,hMnu,[esi+12],MF_BYCOMMAND or MF_ENABLED
			; Step &Into
			invoke EnableMenuItem,hMnu,[esi+16],MF_BYCOMMAND or MF_ENABLED
			; Step &Over
			mov		eax,MF_BYCOMMAND or MF_GRAYED
			.if dbg.inxsource
				mov		eax,MF_BYCOMMAND or MF_ENABLED
			.endif
			invoke EnableMenuItem,hMnu,[esi+20],eax
		.else
			; &Stop
			invoke EnableMenuItem,hMnu,[esi+12],MF_BYCOMMAND or MF_GRAYED
			; Step &Into
			invoke EnableMenuItem,hMnu,[esi+16],MF_BYCOMMAND or MF_GRAYED
			; Step &Over
			invoke EnableMenuItem,hMnu,[esi+20],MF_BYCOMMAND or MF_GRAYED
			; Run &To Caret
			invoke EnableMenuItem,hMnu,[esi+24],MF_BYCOMMAND or MF_GRAYED
		.endif
	.else
		; No project loaded, disable all
		.while dword ptr [esi]
			invoke EnableMenuItem,hMnu,[esi],MF_BYCOMMAND or MF_GRAYED
			add		esi,4
		.endw
	.endif
	ret

EnableMenu endp

FindLine proc uses ebx esi edi,Address:DWORD
	LOCAL	inx:DWORD
	LOCAL	lower:DWORD
	LOCAL	upper:DWORD

	mov		eax,dbg.lastadr
	.if Address>eax
		mov		Address,eax
	.endif
	mov		eax,dbg.inxline
	mov		lower,0
	mov		upper,eax
	.while TRUE
		mov		eax,upper
		sub		eax,lower
		.break .if !eax
		shr		eax,1
		add		eax,lower
		mov		inx,eax
		call	Compare
		.if sdword ptr eax<0
			; Smaller
			mov		eax,inx
			mov		upper,eax
		.elseif sdword ptr eax>0
			; Larger
			mov		eax,inx
			mov		lower,eax
		.else
			; Found
			jmp		Ex
		.endif
	.endw
	; Not found, should never happend
	call	Linear
  Ex:
	mov		eax,edi
	ret

Compare:
	call	GetPointerFromInx
	mov		eax,Address
	sub		eax,[edi].DEBUGLINE.Address
	retn

GetPointerFromInx:
	mov		eax,inx
	mov		edx,sizeof DEBUGLINE
	mul		edx
	mov		edi,dbg.hMemLine
	lea		edi,[edi+eax]
	retn

Linear:
	mov		ebx,dbg.inxline
	mov		edi,dbg.hMemLine
	mov		eax,Address
	.while ebx
		.if eax==[edi].DEBUGLINE.Address
			retn
		.elseif eax<[edi].DEBUGLINE.Address
			lea		edi,[edi-sizeof DEBUGLINE]
			retn
		.endif
		lea		edi,[edi+sizeof DEBUGLINE]
		dec		ebx
	.endw
	lea		edi,[edi-sizeof DEBUGLINE]
	retn

FindLine endp

GetPredefinedDatatype proc uses esi edi,lpType:DWORD

	mov		edi,offset datatype
	.while [edi].DATATYPE.lpszType
		invoke lstrcmpi,[edi].DATATYPE.lpszType,lpType
		.if !eax
			mov		eax,[edi].DATATYPE.lpszConvertType
			jmp		Ex
		.endif
		lea		edi,[edi+sizeof DATATYPE]
	.endw
	xor		eax,eax
  Ex:
	ret

GetPredefinedDatatype endp

FindSymbol proc uses esi,lpName:DWORD

	;Get pointer to symbol list
	mov		esi,dbg.hMemSymbol
	;Loop trough the symbol list
	.while [esi].DEBUGSYMBOL.szName
		invoke lstrcmp,lpName,addr [esi].DEBUGSYMBOL.szName
		.if !eax
			mov		eax,esi
			jmp		Ex			
		.endif
		;Move to next symbol
		lea		esi,[esi+sizeof DEBUGSYMBOL]
	.endw
	; Not found
	xor		eax,eax
  Ex:
	ret

FindSymbol endp

FindLocalVar proc uses esi edi,lpName:DWORD,lpLocal:DWORD,nOfs:DWORD,nMove:DWORD
	LOCAL	nArray:DWORD
	LOCAL	szArray[64]:BYTE

	mov		esi,lpLocal
	mov		edi,nOfs
	.while byte ptr [esi+sizeof DEBUGVAR]
		invoke lstrcmp,addr [esi+sizeof DEBUGVAR],lpName
		.if !eax
			.if sdword ptr nMove<0
				sub		edi,edx
			.endif
			invoke lstrlen,addr [esi+sizeof DEBUGVAR]
			invoke lstrcpy,addr var.szArray,addr [esi+eax+1+sizeof DEBUGVAR]
			mov		eax,[esi].DEBUGVAR.nSize
			mov		var.nSize,eax
			mov		eax,[esi].DEBUGVAR.nArray
			mov		var.nArray,eax
			; Return offset
			mov		eax,edi
			jmp		Ex
		.endif
		.if sdword ptr nMove>0
			add		edi,edx
		.else
			sub		edi,edx
		.endif
		lea		esi,[esi+sizeof DEBUGVAR]
		invoke lstrlen,esi
		lea		esi,[esi+eax+1]
		invoke lstrlen,esi
		lea		esi,[esi+eax+1]
	.endw
	xor		eax,eax
  Ex:
	ret

FindLocalVar endp

FindLocal proc uses esi,lpName:DWORD,nLine:DWORD
	LOCAL	nOfs:DWORD
	LOCAL	nSize:DWORD

	mov		esi,dbg.lpProc
	invoke FindLine,[esi].DEBUGSYMBOL.Address
	push	eax
	mov		eax,[esi].DEBUGSYMBOL.Address
	add		eax,[esi].DEBUGSYMBOL.nSize
	invoke FindLine,eax
	pop		edx
	.if edx && eax
		mov		edx,[edx].DEBUGLINE.LineNumber
		dec		edx
		mov		eax,[eax].DEBUGLINE.LineNumber
		dec		eax
		.if nLine>=edx && nLine<eax
			; PROC Parameter
			invoke FindLocalVar,lpName,[esi].DEBUGSYMBOL.lpType,8,1
			.if eax
				mov		edx,dbg.context.regEbp
				add		eax,edx
				mov		var.Address,eax
				invoke lstrcpy,addr var.szName,lpName
				invoke lstrcpy,addr var.szType,addr szvartype
				mov		eax,'P'
				jmp		Ex
			.else
				; LOCAL
				invoke lstrlen,[esi].DEBUGSYMBOL.lpType
				add		eax,[esi].DEBUGSYMBOL.lpType
				inc		eax
				invoke FindLocalVar,lpName,eax,0,-1
				.if eax
					mov		edx,dbg.context.regEbp
					add		eax,edx
					mov		var.Address,eax
					invoke lstrcpy,addr var.szName,lpName
					invoke lstrcpy,addr var.szType,addr szvartype
					mov		eax,'L'
					jmp		Ex
				.endif
			.endif
		.endif
	.endif
	xor		eax,eax
  Ex:
	ret

FindLocal endp

FindReg proc uses esi,lpName:DWORD

	mov		esi,offset reg32
	.while [esi].REG.szName
		invoke lstrcmpi,lpName,addr [esi].REG.szName
		.if !eax
			mov		eax,esi
			jmp		Ex
		.endif
		lea		esi,[esi+sizeof REG]
	.endw
	xor		eax,eax
  Ex:
	ret

FindReg endp

FindVar proc uses esi edi,lpName:DWORD,nLine:DWORD

	invoke RtlZeroMemory,addr var,sizeof var
	invoke FindReg,lpName
	.if eax
		; REGISTER
		mov		esi,eax
		invoke lstrcpy,addr var.szName,lpName
		mov		eax,[esi].REG.nSize
		mov		var.nSize,eax
		mov		eax,[esi].REG.nOfs
		lea		eax,[dbg.context+eax]
		mov		var.Address,eax
		mov		eax,'R'
		jmp		Ex
	.endif
	.if dbg.lpProc && nRadASMVer>=2217
		; Is in a proc, find parameter or local
		invoke FindLocal,lpName,nLine
		.if eax
			jmp		Ex
		.endif
	.endif
	; Global
	mov		eax,lpName
	.if word ptr [eax]==':z' || word ptr [eax]==':Z'
		mov		var.IsSZ,TRUE
		add		eax,2
	.endif
	invoke FindSymbol,eax
	.if eax
		mov		esi,eax
		invoke lstrcpy,addr var.szName,addr [esi].DEBUGSYMBOL.szName
		.if [esi].DEBUGSYMBOL.nType=='p'
			; PROC
			mov		var.nType,99
			mov		eax,[esi].DEBUGSYMBOL.nSize
			mov		var.nSize,eax
			mov		eax,[esi].DEBUGSYMBOL.Address
			mov		var.Address,eax
			mov		eax,'p'
			jmp		Ex
		.elseif [esi].DEBUGSYMBOL.nType=='d'
			; GLOBAL
			mov		eax,[esi].DEBUGSYMBOL.Address
			mov		var.Address,eax
			mov		eax,[esi].DEBUGSYMBOL.nSize
			mov		var.nSize,eax
			mov		eax,[esi].DEBUGSYMBOL.nArray
			mov		var.nArray,eax
			movzx	eax,[esi].DEBUGSYMBOL.nType
			mov		var.nType,eax
			mov		esi,[esi].DEBUGSYMBOL.lpType
			; Point to type
			invoke lstrlen,addr [esi+sizeof DEBUGVAR]
			lea		edi,[esi+eax+1+sizeof DEBUGVAR]
			invoke lstrcat,addr var.szName,edi
			mov		eax,'d'
			jmp		Ex
		.endif
	.else
		invoke IsHex,lpName
		.if eax
			invoke HexToBin,lpName
			mov		var.Value,eax
			mov		eax,'H'
			jmp		Ex
		.else
			invoke IsDec,lpName
			.if eax
				invoke DecToBin,lpName
				mov		var.Value,eax
				mov		eax,'D'
				jmp		Ex
			.endif
		.endif
	.endif
	xor		eax,eax
  Ex:
	ret

FindVar endp

GetVarVal proc lpName:DWORD,nLine:DWORD,fShow:DWORD

	mov		var.Value,0
	invoke FindVar,lpName,nLine
	.if eax=='R'
		; REGISTER
		mov		eax,var.Address
		mov		eax,[eax]
		mov		edx,var.nSize
		.if edx==2
			movzx	eax,ax
			mov		edx,offset szReg16
		.elseif edx==1
			movzx	eax,al
			mov		edx,offset szReg8
		.elseif edx==3
			movzx	eax,ah
			mov		edx,offset szReg8
		.else
			mov		edx,offset szReg32
		.endif
		mov		var.Value,eax
		.if fShow
			invoke wsprintf,addr outbuffer,edx,addr var.szName,var.Value
		.endif
	.elseif eax=='p'
		; PROC
		.if fShow
			invoke wsprintf,addr outbuffer,addr szProc,addr var.szName,var.nSize
		.else
			xor		eax,eax
			jmp		Ex
		.endif
	.elseif eax=='d'
		; GLOBAL
		mov		eax,var.nType
		.if eax
			; Known type
			.if var.IsSZ
				mov		eax,var.nArray
				sub		eax,var.nOfs
				.if eax>256
					mov		eax,256
				.endif
				invoke ReadProcessMemory,dbg.hdbghand,var.Address,addr var.szValue,eax,0
				.if fShow
					invoke wsprintf,addr outbuffer,addr szDataSZ,addr var.szName,var.Address,var.nSize,addr var.szValue
				.endif
			.else
				.if eax>4
					mov		eax,4
				.endif
				push	eax
				invoke ReadProcessMemory,dbg.hdbghand,var.Address,addr var.Value,eax,0
				pop		eax
				.if fShow
					mov		edx,offset szData32
					.if eax==1
						mov		edx,offset szData8
					.elseif eax==2
						mov		edx,offset szData16
					.endif
					invoke wsprintf,addr outbuffer,edx,addr var.szName,var.Address,var.nSize,var.Value,var.Value
				.endif
			.endif
		.else
			; Unknown type
			.if fShow
				invoke wsprintf,addr outbuffer,addr szData,addr var.szName,var.Address,var.nSize
			.else
				xor		eax,eax
				jmp		Ex
			.endif
		.endif
	.elseif eax=='P'
		; PROC Parameter
		invoke ReadProcessMemory,dbg.hdbghand,var.Address,addr var.Value,var.nSize,0
		.if fShow
			invoke wsprintf,offset outbuffer,addr szParam,addr var.szName,addr var.szArray,addr var.szType,var.Address,var.Value,var.Value
		.endif
	.elseif eax=='L'
		; LOCAL
		invoke ReadProcessMemory,dbg.hdbghand,var.Address,addr var.Value,var.nSize,0
		.if fShow
			invoke wsprintf,offset outbuffer,addr szLocal,addr var.szName,addr var.szArray,addr var.szType,var.Address,var.Value,var.Value
		.endif
	.elseif eax=='H' || eax=='D'
		.if fShow
			invoke wsprintf,offset outbuffer,addr szValue,var.Value,var.Value
		.endif
	.else
		xor		eax,eax
		jmp		Ex
	.endif
	mov		eax,TRUE
  Ex:
	ret

GetVarVal endp

GetVarAdr proc lpName:DWORD,nLine:DWORD

	invoke FindVar,lpName,nLine
	.if eax=='R' || eax=='P' || eax=='L'
		; REGISTER, PROC Parameter or LOCAL
	.elseif eax=='d'
		; GLOBAL
		.if !var.nType
			xor		eax,eax
		.endif
	.else
		xor		eax,eax
		jmp		Ex
	.endif
  Ex:
	ret

GetVarAdr endp
